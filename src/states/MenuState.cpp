#include "MenuState.h"

MenuState::MenuState(StateHandler& handler, sf::RenderWindow& window)
    : stateHandler(handler), window(window)
{
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    buttons.push_back(std::make_unique<PlayButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 200), font, stateHandler, window));
    buttons.push_back(std::make_unique<SettingsButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 300), font, stateHandler, window));
    buttons.push_back(std::make_unique<ExitButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 400), font, window));

}

void MenuState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (auto& button : buttons) {
                    if (button->isMouseOver(window)) {
                        button->onClick();
                    }
                }
            }
        }
    }
}

void MenuState::update(float dt) {
    for (auto& button : buttons) {
        button->update(window); 
    }
}

void MenuState::render(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button->render(window);
    }
}
