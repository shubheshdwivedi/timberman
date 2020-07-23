
#include <include/GameManager.h>

void GameManager::generateTimebar() {
	timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(sf::Color::White);
	timeBar.setPosition(
		(GameConstants::VIDEO_WIDTH / 2) - timeBarStartWidth / 2, GameConstants::VIDEO_HEIGHT - 100);

	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
}

void GameManager::moveBee(sf::Time dt) {
	if (!isBeeActive) {
		srand((int)time(0) * 10);
		beeSpeed = (rand() % 200) + 300;
		isBeeActive = scene.moveBee(GameConstants::VIDEO_WIDTH - 10, isBeeActive, 10, 500, 500);
	}
	else {

		float posX = beeSpeed * dt.asSeconds();
		isBeeActive = scene.moveBee(posX, isBeeActive, 10, 500, 500);
	}
}

void GameManager::moveClouds(sf::Time dt) {
	for (int i = 0; i < GameConstants::NUMBER_OF_CLOUDS; i++)
	{
		if (!isCloudActive[i]) {
			srand((int)time(0) * i);
			cloudSpeeds[i] = (rand() % 200);

			isCloudActive[i] = scene.moveCloud(i, -200, isCloudActive[i], i, 150, 0);

		}
		else {
			float posX = cloudSpeeds[i] * dt.asSeconds();
			isCloudActive[i] = scene.moveCloud(i, posX, isCloudActive[i], i, 150, 0);
		}

	}
}

void GameManager::acceptKeypress(GameConstants::DIRECTION dir) {
	score++;
	timeRemaining += (2 / score) + 0.15;
	acceptInput = false;
	logActive = true;

	if (dir == GameConstants::DIRECTION::RIGHT)
		logSpeedX = -5000;
	else
		logSpeedX = 5000;

	scene.keyPressSceneUpdate(dir);
	scene.updateBranchesPos(score);
	scene.setScoreText(score);
	chop.play();
}

void GameManager::checkForDeath() {

	if (scene.checkForDeath(playerSide)) {
		isPaused = true;
		acceptInput = false;
		death.play();
	}
}

void GameManager::Play() {
	sf::VideoMode vm(GameConstants::VIDEO_WIDTH, GameConstants::VIDEO_HEIGHT);
	sf::RenderWindow window(vm, GameConstants::TITLE, sf::Style::Default);
	sf::Clock clock;

	generateTimebar();

	while (window.isOpen()) {

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyReleased && !isPaused) {
				acceptInput = true;
				scene.resetAxe();
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			isPaused = false;
			score = 0;
			timeRemaining = 6.0f;
			acceptInput = true;

			scene.resetBranches();
			scene.resetAxe();
			scene.resetRIPStone();
		}

		if (acceptInput) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				playerSide = GameConstants::DIRECTION::RIGHT;
				acceptKeypress(playerSide);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				playerSide = GameConstants::DIRECTION::LEFT;
				acceptKeypress(playerSide);
			}


		}
		if (!isPaused) {

			sf::Time dt = clock.restart();

			timeRemaining -= dt.asSeconds();

			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if (timeRemaining <= 0.0f) {
				isPaused = true;
				scene.setMessageText("You ran out of time!");
				oot.play();
			}

			moveBee(dt);
			moveClouds(dt);
			scene.updateBranches();

			if (logActive) {
				float posX = logSpeedX * dt.asSeconds();
				float posY = logSpeedY * dt.asSeconds();
				logActive = scene.moveLog(posX, posY);
			}

			checkForDeath();
		}

		scene.draw(window, isPaused);
		window.draw(timeBar);
		window.display();
	}

}