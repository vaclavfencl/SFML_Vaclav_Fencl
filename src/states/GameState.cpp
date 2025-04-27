#include "GameState.h"
#include "../states/MenuState.h"
#include "PauseState.h"

GameState::GameState(StateHandler& handler, sf::RenderWindow& window)
    : stateHandler(handler), game(window) {}

void GameState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            stateHandler.pushState(std::make_shared<PauseState>(stateHandler, window));
        }
    }
}

void GameState::update(float dt) {
    game.update(dt); 
}

void GameState::render(sf::RenderWindow& window) {
    game.render();
}
