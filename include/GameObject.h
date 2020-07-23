#pragma once
#include<SFML/Graphics.hpp>
#include "include/GameConstants.h"

class GameObject {

	sf::Texture objectTexture;
	sf::Sprite objectSprite;

public:

	void initObject(
		std::string path,
		sf::Vector2f position,
		sf::Vector2f scale = sf::Vector2f(0.6, 0.6),
		sf::Vector2f origin = sf::Vector2f(0, 0));

	void setObjectToCenter();

	void updatePosition(sf::Vector2f position);

	void positionPlayer(GameObject& tree, GameConstants::DIRECTION dir);

	void positionAxe(GameObject& player, GameConstants::DIRECTION dir);

	void positionLog(GameObject& tree);

	void resetObject(float posX, float posY);

	void displayRipStone(GameObject& player, GameObject& axe);

	bool updateBeeObject(
		float posX, bool active, int seed, int heightMod, float heightOffset);

	bool updateCloudObject(
		float posX, bool active, int seed, int heightMod, float heightOffset);

	bool updateLogObject(GameObject& tree, float posX, float posY);

	void positionBranch(int posX, int height, float rotation);

	void drawObject(sf::RenderWindow& window);
};
