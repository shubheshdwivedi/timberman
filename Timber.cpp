

#include <SFML/Graphics.hpp>
#include <sstream>


const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];
enum class direction {LEFT, RIGHT, NONE};
direction branchDirection[NUM_BRANCHES];

void updateBranches(int seed) {

	for (int j = NUM_BRANCHES-1; j > 0; j--)
		branchDirection[j] = branchDirection[j - 1];

	srand(seed + (int)time(0));
	int pos = (rand() % 5);
	
	switch (pos) {
		case 0: branchDirection[0] = direction::LEFT;
			break;
		case 1: branchDirection[1] = direction::RIGHT;
			break;
		default:
			branchDirection[2] = direction::NONE;
			break;
	}
}

int pain()
{
	sf::VideoMode vm(1280, 720);
	sf::RenderWindow window(vm, "Timber!", sf::Style::Titlebar);

	sf::Clock clock;

	bool isPaused = true;
	int score = 0;

	sf::Text scoreText;
	sf::Text messageText;

	sf::Font font;
	font.loadFromFile("fonts/PressStart2P.ttf");	

	messageText.setFont(font);
	messageText.setString("Press enter to start the game...");
	messageText.setCharacterSize(20);
	messageText.setFillColor(sf::Color::White);

	scoreText.setFont(font);
	scoreText.setString("Score =  0");
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);

	sf::FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1280 / 2.0f, 720 / 2.0f);

	scoreText.setPosition(20, 20);

	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);
		branches[i].setOrigin(220, 20);
		branches[i].setScale(0.6, 0.6);
	}

	sf::Texture textureBackground;
	textureBackground.loadFromFile("graphics/background-1280-720.png");
	textureBackground.setSmooth(true);

	sf::Sprite spriteBackground;
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);

	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree2.png");
	textureTree.setSmooth(true);

	sf::Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	sf::FloatRect treeRect = spriteTree.getLocalBounds();
	spriteTree.setOrigin(treeRect.left + treeRect.width / 2.0f, 0);
	spriteTree.setPosition((1280/2.0f), 0);
	spriteTree.setScale(0.6, 0.6);

	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	textureBee.setSmooth(true);

	sf::Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 340);
	spriteBee.setScale(0.7, 0.7);

	bool isBeeActive = false;
	float beeSpeed = 0.6f;

	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	textureCloud.setSmooth(true);

	sf::Sprite spriteCloudOne;
	spriteCloudOne.setTexture(textureCloud);
	spriteCloudOne.setPosition(400, 50);

	sf::Sprite spriteCloudTwo;
	spriteCloudTwo.setTexture(textureCloud);
	spriteCloudTwo.setPosition(220, 100);

	sf::Sprite spriteCloudThree;
	spriteCloudThree.setTexture(textureCloud);
	spriteCloudThree.setPosition(770,150);

	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	float cloud1Speed = 0.5f;
	float cloud2Speed = 0.5f;
	float cloud3Speed = 0.5f;

	sf::RectangleShape timebar;
	float timeBarStartsWith = 480;
	float timeBarHeight = 50;

	timebar.setSize(sf::Vector2f(timeBarStartsWith, timeBarHeight));
	timebar.setPosition((1280 / 2.0f) - timeBarStartsWith / 2.0f, 620);
	timebar.setFillColor(sf::Color::Black);

	sf::Time totalGameTime;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartsWith / timeRemaining;


	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	sf::Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	float x = spriteTree.getPosition().x + spriteTree.getLocalBounds().width / 2.0f;
	// float x = spriteTree.getOrigin().x;
;	spritePlayer.setPosition(x, treeRect.height / 2.0f);
	direction playerDirection = direction::LEFT;

	sf::Texture textureRIPStone;
	textureRIPStone.loadFromFile("graphics/rip.png");
	sf::Sprite spriteRIPStone;
	spriteRIPStone.setTexture(textureRIPStone);
	spriteRIPStone.setPosition(600, 860);

	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	spriteAxe.setPosition(700, 830);


	const float AXE_POSITION_LEFT = 600;
	const float AXE_POSITION_RIGHT = 800;

	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	sf::Sprite spriteLog;
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(700, 830);

	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;


	bool acceptInput = false;

 	while (window.isOpen())	 {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyReleased && !isPaused) {
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
;			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			isPaused = false;
				
			score = 0;
			timeRemaining = 6.0f;

			for (int i = 0; i < NUM_BRANCHES; i++)
				branchDirection[i] = direction::NONE;

			spriteRIPStone.setPosition(675, 2000);

			spritePlayer.setPosition(580, 720);
			acceptInput = true;
		}	
		
		if (acceptInput) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				
				playerDirection = direction::RIGHT;
				score++;

				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(600, 420);
			}

			updateBranches(score);

			spriteLog.setPosition(400,511);

			logSpeedX = -5000;
			logActive = true;

			acceptInput = false;
		}
		
		if (!isPaused) {

			sf::Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();

			timebar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				isPaused = true;

				messageText.setString("You ran out of time!");
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1280 / 2.0f, 720 / 2.0f);
			}

			if (!isBeeActive) {

				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 00) + 300;
				spriteBee.setPosition(1300, height);
				isBeeActive = true;

			}
			else {

				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				if (spriteBee.getPosition().x < -100)
					isBeeActive = false;

			}

			if (!cloud1Active) {
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 200);

				srand((int)time(0) * 10);
				float height = (rand() % 150);
				spriteCloudOne.setPosition(-200, height);
				cloud1Active = true;
			}
			else {
				spriteCloudOne.setPosition(
					spriteCloudOne.getPosition().x +
					(cloud1Speed * dt.asSeconds()),
					spriteCloudOne.getPosition().y);

				if (spriteCloudOne.getPosition().x > 1300)
					cloud1Active = false;
			}

			if (!cloud2Active) {
				srand((int)time(0) * 20);
				cloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float height = (rand() % 300) - 150;
				spriteCloudTwo.setPosition(-300, height);
				cloud2Active = true;
			}
			else {
				spriteCloudTwo.setPosition(
					spriteCloudTwo.getPosition().x +
					(cloud2Speed * dt.asSeconds()),
					spriteCloudTwo.getPosition().y);

				if (spriteCloudTwo.getPosition().x > 1300)
					cloud2Active = false;
			}

			if (!cloud3Active) {
				srand((int)time(0) * 30);
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float height = (rand() % 450) - 150;
				spriteCloudThree.setPosition(-400, height);
				cloud3Active = true;
			}
			else {
				spriteCloudThree.setPosition(
					spriteCloudThree.getPosition().x +
					(cloud3Speed * dt.asSeconds()),
					spriteCloudThree.getPosition().y);

				if (spriteCloudThree.getPosition().x > 1300)
					cloud3Active = false;
			}

			std::stringstream ss;
			ss << "Score = " << score;
			scoreText.setString(ss.str());

			int branchHeight = 0;
			for (int i = 0; i < NUM_BRANCHES; i++) {
				branchHeight = i * 150;
				if (branchDirection[i] == direction::LEFT) {
					
					branches[i].setPosition(420, branchHeight);
					branches[i].setRotation(180);
				} 
				else if (branchDirection[i] == direction::RIGHT) {
					branches[i].setPosition(860, branchHeight);
					branches[i].setRotation(0);
				}
				else {
					branches[i].setPosition(4000, branchHeight);
				}
			}

			if (logActive) {
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				if (spriteLog.getPosition().x < -100 ||spriteLog.getPosition().x > 2000) {
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

		}

		window.clear();

		window.draw(spriteBackground);
		 
		window.draw(spriteCloudOne);
		window.draw(spriteCloudTwo);
		window.draw(spriteCloudThree);

		window.draw(spriteTree);
	
		window.draw(timebar);

		window.draw(spriteBee);
		
		window.draw(scoreText);

		for (int i = 0; i < NUM_BRANCHES; i++) 
			window.draw(branches[i]);
		
		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteRIPStone);
		window.draw(spriteLog);


		if (isPaused)
			window.draw(messageText);


		window.display();
	}
	
	return 0;
}


