#include <SFML/Graphics.hpp>
#include "src/core/StateHandler.h"
#include "src/core/Settings.h"
#include "src/states/MenuState.h"
#include "src/states/GameState.h"
#include "src/states/PauseState.h"

unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

int main() {
    unsigned int windowStyle = sf::Style::Default; 
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Pong", windowStyle);

    StateHandler stateHandler;
    stateHandler.pushState(std::make_shared<MenuState>(stateHandler, window));

    sf::Clock clock;

    while (window.isOpen()) {
        if (Settings::needsWindowReload) {
            windowStyle = Settings::fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
            window.create(sf::VideoMode(screenWidth, screenHeight), "Pong", windowStyle);
            window.setMouseCursorVisible(true);
            Settings::needsWindowReload = false;
        }

        float dt = clock.restart().asSeconds();

        if (stateHandler.getCurrentState()) {
            stateHandler.getCurrentState()->handleInput(window);
            stateHandler.getCurrentState()->update(dt);

            if (!dynamic_cast<GameState*>(stateHandler.getCurrentState().get()) &&
                !dynamic_cast<PauseState*>(stateHandler.getCurrentState().get())) {
                window.clear();
            }

            stateHandler.getCurrentState()->render(window);
            window.display();
        }
    }

    return 0;
}