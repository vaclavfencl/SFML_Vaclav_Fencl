#include "SettingsButton.h"

SettingsButton::SettingsButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window)
    : Button(size, position, "Settings", font), stateHandler(handler), window(window) {}

void SettingsButton::onClick() {
    stateHandler.changeState(std::make_shared<SettingsState>(stateHandler, window));
}