#include <include/SoundManager.h>

SoundManager::SoundManager(std::string path) {
	soundBuffer.loadFromFile(path);
	sound.setBuffer(soundBuffer);
}

void SoundManager::play() {
	this->sound.play();
}