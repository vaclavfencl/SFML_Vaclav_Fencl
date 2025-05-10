#include "AnimationManager.h"

AnimationManager::AnimationManager()
    : sprite(nullptr), frameCount(0), frameTime(0.f), timer(0.f),
    currentFrame(0), isPlaying(false), looping(true) {}

AnimationManager::AnimationManager(sf::Sprite& sprite, int frameCount, float frameTime, sf::Vector2i frameSize)
    : sprite(&sprite), frameCount(frameCount), frameTime(frameTime),
    timer(0.f), currentFrame(0), isPlaying(true), looping(true), frameSize(frameSize)
{
    sprite.setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
}

void AnimationManager::update(float dt) {
    if (!isPlaying || frameCount <= 1) return;

    timer += dt;
    if (timer >= frameTime) {
        timer -= frameTime;
        currentFrame++;
        if (currentFrame >= frameCount) {
            if (looping) {
                currentFrame = 0;
            }
            else {
                currentFrame = frameCount - 1;
                isPlaying = false;
            }
        }

        sprite->setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
    }
}

void AnimationManager::play() {
    isPlaying = true;
}

void AnimationManager::stop() {
    isPlaying = false;
}

void AnimationManager::reset() {
    currentFrame = 0;
    timer = 0.f;
    if (sprite) {
        sprite->setTextureRect(sf::IntRect(0, 0, frameSize.x, frameSize.y));
    }
}

void AnimationManager::setFrame(int index) {
    if (index >= 0 && index < frameCount) {
        currentFrame = index;
        if (sprite) {
            sprite->setTextureRect(sf::IntRect(currentFrame * frameSize.x, 0, frameSize.x, frameSize.y));
        }
    }
}

void AnimationManager::setLoop(bool loop) {
    looping = loop;
}
