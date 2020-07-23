#include <include/GameObject.h>

void GameObject::initObject(
	std::string path,
	sf::Vector2f position,
	sf::Vector2f scale,
	sf::Vector2f origin) {
	objectTexture.loadFromFile(path);
	objectTexture.setSmooth(true);
	objectSprite.setOrigin(origin);
	objectSprite.setTexture(objectTexture);
	objectSprite.setScale(scale);
	objectSprite.setPosition(position);
}

void GameObject::setObjectToCenter() {
	sf::FloatRect treeRect = objectSprite.getLocalBounds();
	objectSprite.setOrigin(treeRect.left + treeRect.width / 2.0f, objectSprite.getOrigin().y);
}

void GameObject::updatePosition(sf::Vector2f position) {
	objectSprite.setPosition(position);
}

void GameObject::positionPlayer(GameObject& tree, GameConstants::DIRECTION dir) {
	sf::FloatRect treeRect = tree.objectSprite.getLocalBounds();
	sf::FloatRect playerRect = this->objectSprite.getLocalBounds();
	float x = (dir == GameConstants::DIRECTION::LEFT) ?
		tree.objectSprite.getPosition().x - treeRect.width / 2.0f - playerRect.width / 2.0f :
		tree.objectSprite.getPosition().x + playerRect.width / 2.0f + 80;

	this->objectSprite.setPosition(x, (treeRect.height / 2.0f) - 45);
}

void GameObject::positionAxe(GameObject& player, GameConstants::DIRECTION dir) {
	sf::FloatRect playerRect = player.objectSprite.getLocalBounds();
	sf::FloatRect axeRect = this->objectSprite.getLocalBounds();
	float x = (dir == GameConstants::DIRECTION::LEFT) ?
		player.objectSprite.getPosition().x + 80 :
		player.objectSprite.getPosition().x - 80;

	this->objectSprite.setPosition(x, (player.objectSprite.getPosition().y) + 45);
}

void GameObject::positionLog(GameObject& tree) {
	sf::FloatRect treeRect = tree.objectSprite.getLocalBounds();
	sf::FloatRect logRect = this->objectSprite.getLocalBounds();
	float x = tree.objectSprite.getPosition().x;
	this->objectSprite.setPosition(x, (treeRect.height / 2.0f) - 45);
}


void GameObject::resetObject(float posX, float posY) {
	this->objectSprite.setPosition(posX, posY);
}

void GameObject::displayRipStone(GameObject& player, GameObject& axe) {
	this->objectSprite.setPosition(player.objectSprite.getPosition());
	player.objectSprite.setPosition(-2000, 2000);
	axe.objectSprite.setPosition(-2000, 2000);
}

bool GameObject::updateBeeObject(
	float posX, bool active, int seed, int heightMod, float heightOffset) {
	sf::Sprite sprite = this->objectSprite;

	if (!active) {
		srand((int)time(0) * seed);
		float height = (rand() % heightMod) + heightOffset;
		sprite.setPosition(posX, height);
		this->objectSprite = sprite;
		return true;
	}

	sprite.setPosition((sprite.getPosition().x - posX), sprite.getPosition().y);
	this->objectSprite = sprite;
	if (sprite.getPosition().x < -100)
		return false;

}

bool GameObject::updateCloudObject(
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

bool GameObject::updateLogObject(GameObject& tree, float posX, float posY) {

	this->objectSprite.setPosition(
		this->objectSprite.getPosition().x + posX, this->objectSprite.getPosition().y + posY);
	if (this->objectSprite.getPosition().x < -100 || this->objectSprite.getPosition().x > 2000) {
		this->positionLog(tree);
		return false;
	}

	return true;
}

void GameObject::positionBranch(int posX, int height, float rotation) {
	this->objectSprite.setPosition(posX, height);
	this->objectSprite.setRotation(rotation);
}

void GameObject::drawObject(sf::RenderWindow& window) {
	window.draw(objectSprite);
}
