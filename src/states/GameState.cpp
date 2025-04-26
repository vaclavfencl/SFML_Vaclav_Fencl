#include "GameState.h"
#include "../states/MenuState.h"

GameState::GameState(StateHandler& handler, sf::RenderWindow& window)
    : stateHandler(handler), game(window) {}

void GameState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            stateHandler.changeState(std::make_shared<MenuState>(stateHandler, window));
        }
    }
}


void GameState::update(float dt) {
    game.update();
}

void GameState::render(sf::RenderWindow& window) {
    game.render();
}
