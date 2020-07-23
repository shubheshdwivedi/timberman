#pragma once
#include<SFML/Audio.hpp>


class SoundManager {
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;

	public :
		SoundManager(std::string path);
		void play();
};