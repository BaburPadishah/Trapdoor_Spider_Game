#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <map>


class Bug
{
public:

	Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f* directionArray);
	Bug(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f* directionArray); // switchTime is a dummy parameter in this one
	~Bug();

	void update(float deltaTime, sf::Vector2f* directionArray);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getGlobalBounds() const;
	int getHealth() const { return health; };
	void setCaught(bool caught);
	bool isCaught() const;

	friend std::ostream& operator<<(std::ostream& out, const Bug& c);

private:
	sf::Sprite body;
	Animation animation;
	unsigned int row;
	float speed;
	sf::Vector2f direction;
	bool faceRight;
	bool rightSideUp;
	bool caught; // whether the bug is caught and should be destroyed
	int health; //points to be given to spider if caught
};