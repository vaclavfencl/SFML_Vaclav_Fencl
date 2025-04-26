#include "PlayButton.h"

PlayButton::PlayButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window)
    : Button(size, position, "Play", font), stateHandler(handler), window(window) {}

void PlayButton::onClick() {
    stateHandler.changeState(std::make_shared<GameState>(stateHandler, window));
}
