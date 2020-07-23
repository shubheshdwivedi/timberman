#include<SFML/Graphics.hpp>
#include "SceneManager.h"
#include "SoundManager.h"
class GameManager {
	
	int score = 0;

	float beeSpeed = 0.0f;
	float cloudSpeeds[3] = { 0.0f };
	float timeRemaining = 6.0f;
	float timeBarStartWidth = 400;
	float timeBarHeight = 50;
	float logSpeedX = 0.0f;
	float logSpeedY = 0.0f;
	float timeBarWidthPerSecond;

	bool isPaused = true;
	bool acceptInput = true;
	bool isBeeActive = false;
	bool isCloudActive[3] = { false };
	bool logActive = false;

	sf::Time gameTimeTotal;
	sf::RectangleShape timeBar;
	sf::Event event;

	Scene scene;

	GameConstants::DIRECTION playerSide;


	SoundManager chop = SoundManager(GameConstants::CHOP_SOUND);
	SoundManager death = SoundManager(GameConstants::DEATH_SOUND);
	SoundManager oot = SoundManager(GameConstants::OUT_OF_TIME_SOUND);


	void generateTimebar();

	void moveBee(sf::Time dt);

	void moveClouds(sf::Time dt);

	void acceptKeypress(GameConstants::DIRECTION dir);

	void checkForDeath();

	public:

		void Play();

};