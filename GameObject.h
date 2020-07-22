#pragma once
#include<SFML/Graphics.hpp>
#include <GameConstants.h>

class GameObject {

	sf::Texture objectTexture;
	sf::Sprite objectSprite;

public:

	void initObject(
		std::string path, 
		sf::Vector2f position, 
		sf::Vector2f scale = sf::Vector2f(0.6, 0.6),
		sf::Vector2f origin = sf::Vector2f(0,0) )	 {
		objectTexture.loadFromFile(path);
		objectTexture.setSmooth(true);
		objectSprite.setOrigin(origin);
		objectSprite.setTexture(objectTexture);
		objectSprite.setScale(scale);
		objectSprite.setPosition(position);
	}

	void setObjectToCenter() {
		sf::FloatRect treeRect = objectSprite.getLocalBounds();
		objectSprite.setOrigin(treeRect.left + treeRect.width / 2.0f, objectSprite.getOrigin().y);
	}

	void updatePosition(sf::Vector2f position) {
		objectSprite.setPosition(position);
	}

	void positionPlayer(GameObject& tree, GameConstants::DIRECTION dir) {
		sf::FloatRect treeRect = tree.objectSprite.getLocalBounds();
		sf::FloatRect playerRect = this->objectSprite.getLocalBounds();
		float x = (dir == GameConstants::DIRECTION::LEFT) ?
			tree.objectSprite.getPosition().x - treeRect.width / 2.0f - playerRect.width / 2.0f :
			tree.objectSprite.getPosition().x + playerRect.width / 2.0f + 80;
			
		this->objectSprite.setPosition(x, (treeRect.height / 2.0f) - 45);
	}

	void positionAxe(GameObject& player, GameConstants::DIRECTION dir) {
		sf::FloatRect playerRect = player.objectSprite.getLocalBounds();
		sf::FloatRect axeRect = this->objectSprite.getLocalBounds();
		float x = (dir == GameConstants::DIRECTION::LEFT) ?
			player.objectSprite.getPosition().x + 80 :
			player.objectSprite.getPosition().x - 80;

		this->objectSprite.setPosition(x, (player.objectSprite.getPosition().y ) +45);
	}

	void positionLog(GameObject& tree) {
		sf::FloatRect treeRect = tree.objectSprite.getLocalBounds();
		sf::FloatRect logRect = this->objectSprite.getLocalBounds();
		float x = tree.objectSprite.getPosition().x;
		this->objectSprite.setPosition(x, (treeRect.height / 2.0f) - 45);
	}


	void resetObject(float posX, float posY) {
		this->objectSprite.setPosition(posX, posY);
	}

	void displayRipStone(GameObject& player, GameObject& axe) {
		this->objectSprite.setPosition(player.objectSprite.getPosition());
		player.objectSprite.setPosition(-2000, 2000);
		axe.objectSprite.setPosition(-2000, 2000);
	}

	bool updateBeeObject(
		float posX, bool active, int seed, int heightMod, float heightOffset) {
		sf::Sprite sprite = this->objectSprite;

		if (!active) {
			srand((int)time(0) * seed);
			float height = (rand() % heightMod) + heightOffset;
			sprite.setPosition(posX , height);
			this->objectSprite = sprite;
			return true;
		}

		sprite.setPosition((sprite.getPosition().x - posX), sprite.getPosition().y);
		this->objectSprite = sprite;
		if (sprite.getPosition().x < -100)
			return false;
		
	}

	bool updateCloudObject(
		float posX, bool active, int seed, int heightMod, float heightOffset) {
		sf::Sprite sprite = this->objectSprite;

		if (!active) {
			srand((int)time(0) * seed);
			float height = (rand() % heightMod) + heightOffset;
			sprite.setPosition(posX, height);
			this->objectSprite = sprite;
			return true;
		}

		sprite.setPosition((sprite.getPosition().x + posX), sprite.getPosition().y);
		this->objectSprite = sprite;
		if (sprite.getPosition().x > 1300)
			return false;

	}

	bool updateLogObject(GameObject& tree, float posX, float posY) {
	
		this->objectSprite.setPosition(
			this->objectSprite.getPosition().x + posX, this->objectSprite.getPosition().y + posY);
		if (this->objectSprite.getPosition().x < -100 || this->objectSprite.getPosition().x > 2000) {
			this->positionLog(tree);
			return false;
		}

		return true;
	}

	void positionBranch(int posX, int height, float rotation) {
		this->objectSprite.setPosition(posX, height);
		this->objectSprite.setRotation(rotation);
	}

	void drawObject(sf::RenderWindow& window) {
		window.draw(objectSprite);
	}
};
