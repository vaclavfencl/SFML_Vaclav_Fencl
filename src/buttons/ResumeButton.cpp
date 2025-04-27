#include "ResumeButton.h"
#include "../core/SoundManager.h"

ResumeButton::ResumeButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler)
    : Button(size, position, "Return", font), stateHandler(handler)
{
}

void ResumeButton::onClick() {
    playClickSound();
    stateHandler.popState(); 
}
