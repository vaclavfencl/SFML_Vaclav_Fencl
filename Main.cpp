#include "src/Game.h"
#include "src/core/StateHandler.h"
#include "src/states/MenuState.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pong");

    StateHandler stateHandler;
    stateHandler.changeState(std::make_shared<MenuState>(stateHandler, window));

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        if (stateHandler.getCurrentState()) {
            stateHandler.getCurrentState()->handleInput(window);
            stateHandler.getCurrentState()->update(dt);
            window.clear();
            stateHandler.getCurrentState()->render(window);
            window.display();
        }
    }

    return 0;
}

