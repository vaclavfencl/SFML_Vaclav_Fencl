#include "MultiplayerButton.h"
#include "../states/MultiplayerState.h"

MultiplayerButton::MultiplayerButton(const sf::Vector2f& size, const sf::Vector2f& position, sf::Font& font, StateHandler& handler, sf::RenderWindow& window)
    : Button(size, position, "Multiplayer", font), stateHandler(handler), window(window) {}

void MultiplayerButton::onClick() {
    stateHandler.pushState(std::make_shared<MultiplayerState>(stateHandler, window));
}
