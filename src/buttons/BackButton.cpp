#include "BackButton.h"
#include "../states/MenuState.h"

BackButton::BackButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window)
    : Button(size, position, "Back", font), stateHandler(handler), window(window) {}

void BackButton::onClick() {
    stateHandler.changeState(std::make_shared<MenuState>(stateHandler, window));
}
