#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>

class SoundManager {
public:
    static void loadSound(const std::string& name, const std::string& filepath);
    static void playSound(const std::string& name);

    static void loadMusic(const std::string& filepath);
    static void playMusic(bool loop = true);
    static void stopMusic();

    static void setVolume(float volume);   
    static float getVolume();                

private:
    static std::unordered_map<std::string, sf::SoundBuffer> soundBuffers;
    static std::unordered_map<std::string, sf::Sound> sounds;
    static sf::Music music;
    static float currentVolume;  
};

#endif
