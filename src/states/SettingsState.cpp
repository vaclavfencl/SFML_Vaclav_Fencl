#include "SettingsState.h"

SettingsState::SettingsState(StateHandler& handler, sf::RenderWindow& window) : stateHandler(handler) {
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    infoText.setFont(font);
    infoText.setString("Settings\nPress Backspace to return");
    infoText.setCharacterSize(30);
    infoText.setPosition(200, 250);
}

void SettingsState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::BackSpace)
                stateHandler.popState();
        }
    }
}

void SettingsState::update(float dt) {}

void SettingsState::render(sf::RenderWindow& window) {
    window.draw(infoText);
}