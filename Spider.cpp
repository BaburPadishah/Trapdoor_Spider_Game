#include "Spider.h"
#include <iostream>

Spider::Spider(sf::Texture* texture, sf::Vector2u imageCount, 
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	row = 2;

	body.setTexture(*texture);

	sf::Vector2u image = animation.getCurrentImage();
	image.y = row;
	animation.setCurrentImage(image);
	animation.uvRect.top = image.y * animation.uvRect.height;
	body.setTextureRect(animation.uvRect);
}

void Spider::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

bool Spider::lunge(float deltaTime, bool* delayed)
{
	// we must cycle through only once 
	// set switch time to three times its value in frames 4 and 5
	unsigned int prevImage = animation.getCurrentImage().x;
	animation.update(row, deltaTime, false, true);
	unsigned int curImage = animation.getCurrentImage().x;
	body.setTextureRect(animation.uvRect);

	switch (curImage)
	{
	case 0:
		if (prevImage != 0) // we've cycled through once
		{
			animation.setSwitchTime(0.05f); // had to hardcode switchTime, bad form
			*delayed = false;
			std::cout << "Spider switchTime has been reset." << std::endl;
			return false;
		}
		break;
	case 4:
		if (!(*delayed)) // lengthen time between frames by a certain factor
		{
			animation.setSwitchTime(1.5f); // hardcoding, bad form
			*delayed = true;
			std::cout << "Spider switchTime has been extended." << std::endl;
		}
		break;
	default:
		break;
	}

	//if (curImage == 0 && prevImage != 0) // we've cycled through once
	//{
	//	animation.setSwitchTime(0.05f); // had to hardcode switchTime, bad form
	//	*delayed = false;
	//	std::cout << "Spider switchTime has been reset." << std::endl;
	//	return false;
	//}
	//else if (curImage == 4 && !(*delayed)) // lengthen time between frames by a certain factor
	//{
	//	animation.setSwitchTime(1.5f); // hardcoding, bad form
	//	*delayed = true;
	//	std::cout << "Spider switchTime has been extended." << std::endl;
	//}
	
	return true;
}

void Spider::shift(int direction)
{
	// add direction to row
	row += direction;

	//update animation's uvRect - get current image, change y component, set current image
	sf::Vector2u image = animation.getCurrentImage();
	image.y = row;
	animation.setCurrentImage(image);
	animation.uvRect.top = image.y * animation.uvRect.height;

	//set new body rect
	body.setTextureRect(animation.uvRect);
}

void Spider::resetAnimation()
{
	row = 2;
	animation.setCurrentImage(sf::Vector2u(0, row));
	animation.setSwitchTime(0.05f);
}

unsigned int Spider::getRow() const
{
	return row;
}

sf::Vector2u Spider::getCurrentImage() const
{
	return animation.getCurrentImage();
}

sf::FloatRect Spider::getGlobalBounds() const
{
	return body.getGlobalBounds();
}

void Spider::setRow(unsigned int newRow)
{
	row = newRow;
}

Spider::~Spider()
{
}