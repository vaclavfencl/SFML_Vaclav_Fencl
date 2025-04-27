#include "SoundManager.h"
#include <iostream>

std::unordered_map<std::string, sf::SoundBuffer> SoundManager::soundBuffers;
std::unordered_map<std::string, sf::Sound> SoundManager::sounds;
sf::Music SoundManager::music;
float SoundManager::currentVolume = 50.f; 

void SoundManager::loadSound(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr << "Failed to load sound: " << filepath << std::endl;
        return;
    }

    soundBuffers[name] = buffer;

    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sound.setVolume(currentVolume); 
    sounds[name] = sound;
}

void SoundManager::playSound(const std::string& name) {
    auto it = sounds.find(name);
    if (it != sounds.end()) {
        it->second.play();
    }
}

void SoundManager::loadMusic(const std::string& filepath) {
    if (!music.openFromFile(filepath)) {
        std::cerr << "Failed to load music: " << filepath << std::endl;
    }
    music.setVolume(currentVolume);
}

void SoundManager::playMusic(bool loop) {
    music.setLoop(loop);
    music.play();
}

void SoundManager::stopMusic() {
    music.stop();
}

void SoundManager::setVolume(float volume) {
    currentVolume = volume;
    for (auto it = sounds.begin(); it != sounds.end(); ++it) {
        it->second.setVolume(volume);
    }
    music.setVolume(volume);
}

float SoundManager::getVolume() {
    return currentVolume;
}
