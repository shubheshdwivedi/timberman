#pragma once
#include <SFML/Graphics.hpp>
#include "include/GameObject.h"
#include <sstream>

class Scene {

	sf::Text scoreText;
	sf::Text messageText;
	sf::Font font;

	GameObject background;
	GameObject tree;
	GameObject cloud[3];
	GameObject bee;
	GameObject log;
	GameObject axe;
	GameObject player;
	GameObject ripStone;
	GameObject branches[GameConstants::NUMBER_OF_BRANCHES];

	GameConstants::DIRECTION branchDirection[GameConstants::NUMBER_OF_BRANCHES];

	float branchHeight = 0;

	void setupScoreAndMessage();
	void setupBackground();
	void setupTree();
	void setupBee();
	void setupClouds();
	void setupPlayer();
	void setupAxe();
	void setupRipStone();
	void displayRipStone();
	void setupTimebar();
	void setupBranches();
	void setupLog();

	public :

		Scene();

		void init();
		void draw(sf::RenderWindow& window, bool isPaused);
		void setMessageText(std::string message);
		void setScoreText(int score);

		bool moveBee(float posX, bool active, int seed, int heightMod, float heightOffset);
		bool moveCloud(int cloudNum, float posX, bool active, int seed, int heightMod, float heightOffset);
		bool moveLog(float posX, float posY);
		void updateBranches();

		void resetBranches();
		void updateBranchesPos(int seed);

		void resetAxe();
		void resetRIPStone();

		void keyPressSceneUpdate(GameConstants::DIRECTION dir);
		bool checkForDeath(GameConstants::DIRECTION playerSide);
};