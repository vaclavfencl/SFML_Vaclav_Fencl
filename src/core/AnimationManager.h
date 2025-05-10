#pragma once
#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include <SFML/Graphics.hpp>

class AnimationManager {
public:
    AnimationManager();
    AnimationManager(sf::Sprite& sprite, int frameCount, float frameTime, sf::Vector2i frameSize);

    void update(float dt);
    void play();
    void stop();
    void reset();

    void setFrame(int index);
    void setLoop(bool loop);

private:
    sf::Sprite* sprite;
    int frameCount;
    float frameTime;
    float timer;
    int currentFrame;
    bool isPlaying;
    bool looping;
    sf::Vector2i frameSize;
};

#endif
