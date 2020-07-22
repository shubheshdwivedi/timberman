#pragma once
#include<SFML/Audio.hpp>


class SoundManager {
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	public :
		SoundManager(std::string path) {
			soundBuffer.loadFromFile(path);
			sound.setBuffer(soundBuffer);
		}

		void play() {
			this->sound.play();
		}
};