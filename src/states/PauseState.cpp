#include "PauseState.h"
#include "../buttons/Button.h"
#include "../buttons/BackButton.h"
#include "../core/SoundManager.h"
#include "MenuState.h"

PauseState::PauseState(StateHandler& handler, sf::RenderWindow& window)
    : stateHandler(handler), window(window)
{
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    background.setSize(sf::Vector2f(400, 400));
    background.setFillColor(sf::Color(100, 100, 100, 200)); 
    background.setPosition(200, 100);

    title.setFont(font);
    title.setString("PAUSED");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::Black);
    title.setPosition(320, 130);

    buttons.push_back(std::make_unique<ResumeButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 250), font, stateHandler));
    buttons.push_back(std::make_unique<BackButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 350), font, stateHandler, window));
}

void PauseState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (auto& button : buttons) {
                    if (button->isMouseOver(window)) {
                        button->playClickSound(); 
                        button->onClick();
                    }
                }
            }
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                stateHandler.popState();
            }
        }
    }
}

void PauseState::update(float dt) {
    for (auto& button : buttons) {
        button->update(window);
    }
}

void PauseState::render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(title);

    for (auto& button : buttons) {
        button->render(window);
    }
}
