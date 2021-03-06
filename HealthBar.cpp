#include "HealthBar.h"

HealthBar::HealthBar(sf::Texture* texture, const sf::Vector2u& imageCount,
	float switchTime) :
	animation(texture, imageCount, switchTime)
{
	health = 15;
	body.setTexture(*texture);

	animation.setCurrentImage(sf::Vector2u(0, 0));
	body.setTextureRect(animation.uvRect);
}

int HealthBar::getHealth() const
{
	return health;
}

void HealthBar::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void HealthBar::update(int health, float deltaTime)
{
	this->health += health;
	if (this->health <= 0) // game over, health is gone
	{
		animation.setCurrentImage(sf::Vector2u(15, 0));
	}
	else if (this->health >= 15) // health restored fully
	{
		this->health = 15;
		animation.setCurrentImage(sf::Vector2u(0, 0));
	}
	else // health is between 0 and 15
	{
		// jump sprite back by health added
		int x = animation.getCurrentImage().x - health;
		animation.setCurrentImage(sf::Vector2u(x, 0));
	}

	animation.update(0, deltaTime, false, true);
	body.setTextureRect(animation.uvRect);
}

void HealthBar::reset(float deltaTime)
{
	health = 15;
	animation.setCurrentImage(sf::Vector2u(0, 0));
	animation.update(0, deltaTime, false, true);
	body.setTextureRect(animation.uvRect);
}
