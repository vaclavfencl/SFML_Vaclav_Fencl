#include <SFML/Graphics.hpp>
#include "src/core/StateHandler.h"
#include "src/core/Settings.h"
#include "src/states/MenuState.h"
#include "src/states/GameState.h"
#include "src/states/PauseState.h"
#include "src/core/SoundManager.h"

unsigned int screenWidth = 800;
unsigned int screenHeight = 600;

int main() {
    unsigned int windowStyle = sf::Style::Default; 
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Pong", windowStyle);

    StateHandler stateHandler;
    stateHandler.pushState(std::make_shared<MenuState>(stateHandler, window));

    SoundManager::loadMusic("Thirdparty/sounds/background_music.flac");
    SoundManager::playMusic(true);
    sf::Clock clock;

    while (window.isOpen()) {
        if (Settings::needsWindowReload) {
            windowStyle = Settings::fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
            window.create(sf::VideoMode(screenWidth, screenHeight), "Pong", windowStyle);
            window.setMouseCursorVisible(true);
            Settings::needsWindowReload = false;
        }

        float dt = clock.restart().asSeconds();

        if (auto currentState = stateHandler.getCurrentState()) {
            currentState->handleInput(window);
            currentState->update(dt);

            if (!dynamic_cast<GameState*>(currentState.get()) &&
                !dynamic_cast<PauseState*>(currentState.get())) {
                window.clear();
            }

            currentState->render(window);
            window.display();
        }
    }

    return 0;
}