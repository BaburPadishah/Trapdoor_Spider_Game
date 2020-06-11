#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Window\Mouse.hpp>
#include <iostream>
#include <vector>
#include "Spider.h"
#include "HealthBar.h"
#include "Bug.h"

using std::cout;

static const unsigned int WINDOW_WIDTH = 2 * sf::VideoMode::getDesktopMode().width / 3;
static const unsigned int WINDOW_HEIGHT = 2 * sf::VideoMode::getDesktopMode().height / 3;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Trapdoor", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::Texture bg;
	bg.loadFromFile("png/background.png");
	sf::Sprite bgSprite;
	bgSprite.setTexture(bg);
	unsigned int bgx = bg.getSize().x;
	unsigned int bgy = bg.getSize().y;
	float widthRatio = 1.0f * WINDOW_WIDTH / bgx;
	float heightRatio = 1.0f * WINDOW_HEIGHT / bgy;
	bgSprite.setScale(widthRatio, heightRatio);

	srand(unsigned int(time(NULL))); // initialize random int generator

	sf::Vector2f unitCircle[16]{ // each direction (up, down, left, right) has 7 options
		sf::Vector2f(1.0f, 0.0f), // 0 degrees, 0pi
		sf::Vector2f(sqrtf(3.0f) / 2.0f, 0.5f), // 30 degrees, pi/6
		sf::Vector2f(sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f), // 45 degrees, pi/4
		sf::Vector2f(0.5f, sqrtf(3.0f) / 2.0f), // 60 degrees, pi/3
		sf::Vector2f(0.0f, 1.0f), // 90 degrees, pi/2
		sf::Vector2f(-0.5f, sqrtf(3.0f) / 2.0f), // 120 degrees, 2pi/3
		sf::Vector2f(-sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f), // 135 degrees, 3pi/4
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, 0.5f), // 150 degrees, 5pi/6
		sf::Vector2f(-1.0f, 0.0f), // 180 degrees, pi
		sf::Vector2f(-sqrtf(3.0f) / 2.0f, -0.5f), // 210 degrees, 7pi/6
		sf::Vector2f(-sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f), // 225 degrees, 5pi/4
		sf::Vector2f(-0.5f, -sqrtf(3.0f) / 2.0f), // 240 degrees, 4pi/3
		sf::Vector2f(0.0f, -1.0f), // 270 degrees, 3pi/2
		sf::Vector2f(0.5f, -sqrtf(3.0f) / 2.0f), // 300 degrees, 5pi/3
		sf::Vector2f(sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f), // 315 degrees, 7pi/4 
		sf::Vector2f(sqrtf(3.0f) / 2.0f, -0.5f), // 330 degrees, 11pi/6
	};

	int bugCount = 5;

	sf::Texture bugTexture;
	bugTexture.loadFromFile("png/bugs.png");
	std::vector<Bug> bugVector;
	for (int i = 0; i < bugCount; ++i)
	{
		bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
		std::cout << bugVector.at(i);
	}

	sf::Texture spiderTexture;
	spiderTexture.loadFromFile("png/spider.png"); // orange is E25630, blue is 9fcbf8
	Spider spider(&spiderTexture, sf::Vector2u(6, 5), 0.05f);
	spider.setPosition(WINDOW_WIDTH * 34.0f / 160.0f, 
		WINDOW_HEIGHT * 12.0f / 45.0f);
	spider.setScale(widthRatio, heightRatio);

	// strand rectangles - used to determine where a bug is when its caught
	// goes from left to right
	sf::FloatRect webStrands[5]{
		// left
		sf::FloatRect(40.0f * WINDOW_WIDTH / 160.0f,
			52.0f * WINDOW_HEIGHT / 90.0f,
			30.0f * WINDOW_WIDTH / 160.0f,
			5.0f * WINDOW_HEIGHT / 90.0f),
		// down left
		sf::FloatRect(62.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			17.0f * WINDOW_WIDTH / 160.0f,
			7.0f * WINDOW_HEIGHT / 90.0f),
		// down
		sf::FloatRect(94.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			7.0f * WINDOW_WIDTH / 160.0f,
			10.0f * WINDOW_HEIGHT / 90.0f),
		// down right
		sf::FloatRect(111.0f * WINDOW_WIDTH / 160.0f,
			60.0f * WINDOW_HEIGHT / 90.0f,
			22.0f * WINDOW_WIDTH / 160.0f,
			6.0f * WINDOW_HEIGHT / 90.0f),
		// right
		sf::FloatRect(125.0f * WINDOW_WIDTH / 160.0f,
			52.0f * WINDOW_HEIGHT / 90.0f,
			25.0f * WINDOW_WIDTH / 160.0f,
			3.0f * WINDOW_HEIGHT / 90.0f),
	};


	sf::Texture healthTexture;
	healthTexture.loadFromFile("png/health.png");
	HealthBar health(&healthTexture, sf::Vector2u(16, 1), 20.0f);
	health.setPosition(WINDOW_WIDTH / 32.0f, WINDOW_HEIGHT / 18.0f);
	health.setScale(widthRatio, heightRatio);

	sf::Texture gameOverTexture;
	gameOverTexture.loadFromFile("png/game_over.png");
	sf::Sprite gameOver;
	gameOver.setTexture(gameOverTexture);
	gameOver.setScale(widthRatio, heightRatio);

	sf::Texture quitTexture;
	quitTexture.loadFromFile("png/quit.png");
	sf::Sprite quit;
	quit.setTexture(quitTexture);
	quit.setScale(widthRatio, heightRatio);
	quit.setPosition(3.0f * WINDOW_WIDTH / 160.0f, 80.0f * WINDOW_HEIGHT / 90.0f);

	sf::Texture retryTexture;
	retryTexture.loadFromFile("png/retry.png");
	sf::Sprite retry;
	retry.setTexture(retryTexture);
	retry.setScale(widthRatio, heightRatio);
	retry.setPosition(129.0f * WINDOW_WIDTH / 160.0f, 80.0f * WINDOW_HEIGHT / 90.0f);

	float deltaTime = 0.0f;
	sf::Clock deltaClock; // time between frames
	sf::Clock spawnClock; // time between bugs spawning
	sf::Clock healthClock; // time between health decrements

	bool inLunge = false; // spider is currently lunging (triggers lunge animation)
	bool delayed = false; // spider's switchTime has been extended
	bool gameIsOver = false; // health is zero

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart().asSeconds();


		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:   // window closed
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Escape) 
					{
						window.close(); 
					}
					if ((event.key.code == sf::Keyboard::Left || 
						event.key.code == sf::Keyboard::A) &&
						spider.getRow() > 0 &&
						!inLunge && !gameIsOver)
					{
						spider.shift(-1);
					}
					if ((event.key.code == sf::Keyboard::Right ||
						event.key.code == sf::Keyboard::D) &&
						spider.getRow() < 4 &&
						!inLunge && !gameIsOver)
					{
						spider.shift(1);
					}
					if (event.key.code == sf::Keyboard::Space && !gameIsOver)
					{
						inLunge = true;
						health.update(-1, deltaTime); // Fix needed: holding down space makes health continually drain
						// the bugs should start fleeing when the animation starts
					}
					break;
				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						sf::Vector2i mousePos = sf::Mouse::getPosition(window);
						cout << "Mouseclick position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
						if (quit.getGlobalBounds().contains(sf::Vector2f(mousePos)) && gameIsOver)
						{
							window.close();
						}
						else if (retry.getGlobalBounds().contains(sf::Vector2f(mousePos)) && gameIsOver)
						{
							health.reset();
							spider.resetAnimation(); // Fix needed: the spider does another quick lunge after game is reset
							bugVector.clear();
							for (int i = 0; i < bugCount; ++i)
							{
								bugVector.push_back(Bug(&bugTexture, sf::Vector2u(4, 3), 0.0f, unitCircle));
								std::cout << bugVector.at(i);
							}
							gameIsOver = false;
						}
					}
					break;

			}
		}

		window.clear();
		int curHealth = health.getHealth();
		
		if (curHealth <= 0)
		{
			gameIsOver = true;
		}
		else // update animations only if not game over
		{
			if (inLunge)
			{
				inLunge = spider.lunge(deltaTime, &delayed);
				// check if any of the bugs intersect the spider sprite (all directions)
				for (int i = 0; i < bugCount; ++i)
				{
					if (spider.getGlobalBounds().intersects(bugVector.at(i).getGlobalBounds()))
					{
						// check which strand rectangle the bug is in, if direction spider is facing matches, if its in 4th frame
						// if so, that particular bug is caught
					}
				}
				// if bug is caught - bug goes into caught animation, health.update(bug.getHealth(), deltaTime);
				// increment score
				// else - nothing, health was already decremented
			}
			if (healthClock.getElapsedTime().asSeconds() >= 20.0f) // decrement health every 20 seconds
			{
				healthClock.restart();
				health.update(-1, deltaTime);
			}
			if (spawnClock.getElapsedTime().asSeconds() >= 3.0f) // spawn new bug every three seconds when they get under a certain population
			{
				spawnClock.restart();
				// spawn new bug
			}
			for (int i = 0; i < bugCount; ++i)
			{
				bugVector.at(i).update(deltaTime, unitCircle);
			}
		}

		window.draw(bgSprite);
		spider.draw(window);
		for (int i = 0; i < bugCount; ++i)
		{
			bugVector.at(i).draw(window);
		}
		if (gameIsOver) // game over
		{
			window.draw(gameOver);
			window.draw(retry);
			window.draw(quit);
		}
		health.draw(window);
		window.display();
	}

	return 0;
}



//OBSOLETE
//Point allPoints[18]
//{
//	{10.0f * widthRatio, 50.0f * heightRatio, 'A'}, //A
//	{47.0f * widthRatio, 43.0f * heightRatio, 'B'}, //B
//	{130.0f * widthRatio, 42.0f * heightRatio, 'C'}, //C
//	{146.0f * widthRatio, 31.0f * heightRatio, 'D'}, //D
//	{39.0f * widthRatio, 65.0f * heightRatio, 'E'}, //E
//	{72.0f * widthRatio, 75.0f * heightRatio, 'F'}, //F
//	{85.0f * widthRatio, 62.0f * heightRatio, 'G'}, //G
//	{115.0f * widthRatio, 65.0f * heightRatio, 'H'}, //H
//	{137.0f * widthRatio, 60.0f * heightRatio, 'I'}, //I
//	{30.0f * widthRatio, 78.0f * heightRatio, 'J'}, //J
//	{145.0f * widthRatio, 76.0f * heightRatio, 'K'}, //K
//	{-20.0f * widthRatio, 45.0f * heightRatio, '1'}, //S1
//	{26.0f * widthRatio, 110.0f * heightRatio, '2'}, //S2
//	{51.0f * widthRatio, 110.0f * heightRatio, '3'}, //S3
//	{95.0f * widthRatio, 110.0f * heightRatio, '4'}, //S4
//	{135.0f * widthRatio, 110.0f * heightRatio, '5'}, //S5
//	{180.0f * widthRatio, 70.0f * heightRatio, '6'}, //S6
//	{180.0f * widthRatio, 42.0f * heightRatio, '7'} //S7
//};
//
////path connections
//allPoints[0].connect(allPoints[1]);
//allPoints[0].connect(allPoints[4]);
//allPoints[0].connect(allPoints[9]);
//allPoints[0].connect(allPoints[11]);
//
//allPoints[1].connect(allPoints[0]);
//allPoints[1].connect(allPoints[4]);
//allPoints[1].connect(allPoints[5]);
//allPoints[1].connect(allPoints[6]);
//allPoints[1].connect(allPoints[11]);
//
//allPoints[2].connect(allPoints[3]);
//allPoints[2].connect(allPoints[7]);
//allPoints[2].connect(allPoints[8]);
//allPoints[2].connect(allPoints[16]);
//
//allPoints[3].connect(allPoints[2]);
//allPoints[3].connect(allPoints[8]);
//allPoints[3].connect(allPoints[10]);
//allPoints[3].connect(allPoints[17]);
//
//allPoints[4].connect(allPoints[0]);
//allPoints[4].connect(allPoints[1]);
//allPoints[4].connect(allPoints[5]);
//allPoints[4].connect(allPoints[9]);
//allPoints[4].connect(allPoints[12]);
//
//allPoints[5].connect(allPoints[1]);
//allPoints[5].connect(allPoints[4]);
//allPoints[5].connect(allPoints[6]);
//allPoints[5].connect(allPoints[9]);
//allPoints[5].connect(allPoints[13]);
//
//allPoints[6].connect(allPoints[1]);
//allPoints[6].connect(allPoints[5]);
//allPoints[6].connect(allPoints[7]);
//allPoints[6].connect(allPoints[14]);
//
//allPoints[7].connect(allPoints[6]);
//allPoints[7].connect(allPoints[2]);
//allPoints[7].connect(allPoints[8]);
//allPoints[7].connect(allPoints[14]);
//
//allPoints[8].connect(allPoints[2]);
//allPoints[8].connect(allPoints[7]);
//allPoints[8].connect(allPoints[3]);
//allPoints[8].connect(allPoints[10]);
//allPoints[8].connect(allPoints[15]);
//
//allPoints[9].connect(allPoints[0]);
//allPoints[9].connect(allPoints[4]);
//allPoints[9].connect(allPoints[5]);
//allPoints[9].connect(allPoints[13]);
//
//allPoints[10].connect(allPoints[3]);
//allPoints[10].connect(allPoints[8]);
//allPoints[10].connect(allPoints[15]);
//
//allPoints[11].connect(allPoints[0]);
//allPoints[11].connect(allPoints[1]);
//
//allPoints[12].connect(allPoints[4]);
//
//allPoints[13].connect(allPoints[9]);
//allPoints[13].connect(allPoints[5]);
//
//allPoints[14].connect(allPoints[6]);
//allPoints[14].connect(allPoints[7]);
//
//allPoints[15].connect(allPoints[8]);
//allPoints[15].connect(allPoints[10]);
//
//allPoints[16].connect(allPoints[2]);
//
//allPoints[17].connect(allPoints[3]);
//
//// edges within range: B to E, B to F, B to G, G to F, G to S4, G to H,
//// H to C, H to S4, H to I, H to S5, D to I


//Bug bug0(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug1(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug2(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug3(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//Bug bug4(&bugTexture, sf::Vector2u(4, 3), 0.3f, allPoints);
//
//// Failed paths
//std::list<const Point*> failPath0 = { &allPoints[11], &allPoints[1] }; // S1 to B
//std::list<const Point*> failPath1 = { &allPoints[12], &allPoints[4] }; // S2 to E
//std::list<const Point*> failPath2 = { &allPoints[13], &allPoints[5] }; // S3 to F
//std::list<const Point*> failPath3 = { &allPoints[14], &allPoints[7] }; // S4 to H
//std::list<const Point*> failPath4 = { &allPoints[15], &allPoints[9] }; // S5 to I
//std::list<const Point*> failPath5 = { &allPoints[15], &allPoints[10] }; // S5 to K