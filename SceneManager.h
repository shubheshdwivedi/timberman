#pragma once
#include <SFML/Graphics.hpp>
#include <GameObject.h>
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

	void setupScoreAndMessage() {
		messageText.setFont(font);
		messageText.setCharacterSize(20);
		messageText.setFillColor(sf::Color::White);
		setMessageText(GameConstants::GREETINGS);

		scoreText.setFont(font);
		scoreText.setCharacterSize(40);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(20, 20);
		setScoreText(0);
	}

	void setupBackground() {
		background.initObject(GameConstants::BACKGROUND_PATH, sf::Vector2f(0, 0), sf::Vector2f(1, 1));
	}

	void setupTree() {
		tree.initObject(GameConstants::TREE_PATH, sf::Vector2f((GameConstants::VIDEO_WIDTH / 2.0f), 0));
		tree.setObjectToCenter();
	}

	void setupBee() {
		bee.initObject(GameConstants::BEE_PATH, sf::Vector2f(300, 400));
	}

	void setupClouds() {
		sf::Vector2f scales[3]{ sf::Vector2f(1,1), sf::Vector2f(0.6, 0.6), sf::Vector2f(0.8,0.8) };
		for (int i = 0; i < 3; i++)
			cloud[i].initObject(GameConstants::CLOUD_PATH, sf::Vector2f(0, i * 50), scales[i]);
	}

	void setupPlayer() {
		player.initObject(GameConstants::PLAYER_PATH, sf::Vector2f(0, 0), sf::Vector2f(0.7, 0.7));
		player.positionPlayer(tree, GameConstants::DIRECTION::RIGHT);
	}

	void setupAxe() {
		axe.initObject(GameConstants::AXE_PATH, sf::Vector2f(-2000, -2000), sf::Vector2f(0.6, 0.6));
		
	}

	void setupRipStone() {
		ripStone.initObject(GameConstants::RIPSTONE_PATH, sf::Vector2f(-2000, -2000), sf::Vector2f(0.6, 0.6));
	}

	void displayRipStone() {
		ripStone.displayRipStone(player, axe);
	}

	void setupTimebar() {

		sf::RectangleShape timebar;
		float timeBarStartsWith = 480;
		float timeBarHeight = 50;

		timebar.setSize(sf::Vector2f(timeBarStartsWith, timeBarHeight));
		timebar.setPosition((1280 / 2.0f) - timeBarStartsWith / 2.0f, 620);
		timebar.setFillColor(sf::Color::Black);

		sf::Time totalGameTime;
		float timeRemaining = 6.0f;
		float timeBarWidthPerSecond = timeBarStartsWith / timeRemaining;
	}

	void setupBranches() {
		for (int i = 0; i < GameConstants::NUMBER_OF_BRANCHES; i++) {
			branches[i].initObject(
				GameConstants::BRANCH_PATH, sf::Vector2f(-2000, -2000), sf::Vector2f(0.6, 0.6), sf::Vector2f(220,20));
		}
	}

	void setupLog() {
		log.initObject(GameConstants::LOG_PATH, sf::Vector2f(0, 0));
		log.setObjectToCenter();
		log.positionLog(tree);
	}

	public :

		Scene() {
			sf::VideoMode vm(GameConstants::VIDEO_WIDTH, GameConstants::VIDEO_HEIGHT);
			sf::RenderWindow window(vm, GameConstants::TITLE, sf::Style::Titlebar);
			font.loadFromFile(GameConstants::FONT_FAMILY);
			init();
		}

		void init() {
			setupScoreAndMessage();
			setupBackground();
			setupTree();
			setupBee();
			setupClouds();
			setupPlayer();
			setupAxe();
			setupRipStone();
			setupBranches();
			setupLog();
		}

		void draw(sf::RenderWindow &window, bool isPaused) {
			background.drawObject(window);
			
			for (int i = 0;i < GameConstants::NUMBER_OF_CLOUDS; i++)
				cloud[i].drawObject(window);
			
			tree.drawObject(window);
			for (int i = 0; i < GameConstants::NUMBER_OF_BRANCHES; i++) 
				branches[i].drawObject(window);
			
			player.drawObject(window);
			axe.drawObject(window);

			log.drawObject(window);

			ripStone.drawObject(window);
			bee.drawObject(window);
			

			window.draw(scoreText);
			if(isPaused)
				window.draw(messageText);
		}

		void setMessageText(std::string message) {
			messageText.setString(message);
			sf::FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
			messageText.setPosition(GameConstants::VIDEO_WIDTH / 2.0f, GameConstants::VIDEO_HEIGHT/ 2.0f);
		}

		void setScoreText(int score) {
			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());
		}

		bool moveBee(float posX, bool active, int seed, int heightMod, float heightOffset) {
			return bee.updateBeeObject(posX, active, seed, heightMod, heightOffset);
		}

		bool moveCloud(int cloudNum, float posX, bool active, int seed, int heightMod, float heightOffset) {
			return cloud[cloudNum].updateCloudObject(posX, active, seed, heightMod, heightOffset);
		}

		bool moveLog(float posX, float posY) {
			return log.updateLogObject(tree, posX, posY);
		}

		void updateBranches() {
			for (int i = 0; i < GameConstants::NUMBER_OF_BRANCHES; i++) {
				branchHeight = (i) * 150;
				if (branchDirection[i] == GameConstants::DIRECTION::LEFT)
					branches[i].positionBranch(420, branchHeight, 180);
				else if (branchDirection[i] == GameConstants::DIRECTION::RIGHT)
					branches[i].positionBranch(860, branchHeight, 0);
				else
					branches[i].positionBranch(4000, branchHeight, 0);
			}
		}

		void resetBranches() {
			for (int i = 0; i < GameConstants::NUMBER_OF_BRANCHES; i++)
				branchDirection[i] = GameConstants::DIRECTION::NONE;	
		}

		void updateBranchesPos(int seed) {

			for (int j =GameConstants::NUMBER_OF_BRANCHES - 1; j > 0; j--)
				branchDirection[j] = branchDirection[j - 1];

			srand(seed + (int)time(0));
			int pos = (rand() % 5);

			switch (pos) {
			case 0: branchDirection[0] = GameConstants::DIRECTION::LEFT;
				break;
			case 1: branchDirection[0] = GameConstants::DIRECTION::RIGHT;
				break;
			default:
				branchDirection[0] = GameConstants::DIRECTION::NONE;
				break;
			}
		}

		void resetAxe() {
			axe.resetObject(-2000, -2000);
		}

		void resetRIPStone() {
			ripStone.resetObject(-2000, -2000);
			player.positionPlayer(tree, GameConstants::DIRECTION::RIGHT);
		}

		void keyPressSceneUpdate(GameConstants::DIRECTION dir) {
			player.positionPlayer(tree, dir);
			axe.positionAxe(player, dir);
		}

		bool checkForDeath(GameConstants::DIRECTION playerSide) {
			if (branchDirection[GameConstants::NUMBER_OF_BRANCHES - 1] == playerSide) {
				displayRipStone();
				setMessageText("Oops! Squished");
				return true;
			}
			return false;
		}

};