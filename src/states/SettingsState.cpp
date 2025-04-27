#include "SettingsState.h"

SettingsState::SettingsState(StateHandler& handler, sf::RenderWindow& window)
    : stateHandler(handler), window(window)
{
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    infoText.setFont(font);
    infoText.setString("Settings");
    infoText.setCharacterSize(30);
    infoText.setPosition(320, 100);

    optionButtons.push_back(std::make_unique<VolumeButton>(sf::Vector2f(300, 60), sf::Vector2f(250, 200), font));
    optionButtons.push_back(std::make_unique<FullscreenButton>(sf::Vector2f(300, 60), sf::Vector2f(250, 300), font));

    backButton = std::make_unique<BackButton>(sf::Vector2f(200, 60), sf::Vector2f(300, 450), font, stateHandler, window);
}

void SettingsState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                for (auto& button : optionButtons) {
                    if (button->isMouseOver(window)) {
                        button->onClick();
                    }
                }

                if (backButton->isMouseOver(window)) {
                    backButton->playClickSound();
                    backButton->onClick();
                }
            }
        }
    }
}

void SettingsState::update(float dt) {
    for (auto& button : optionButtons) {
        button->update(window);
    }
    backButton->update(window);
}

void SettingsState::render(sf::RenderWindow& window) {
    window.draw(infoText);

    for (auto& button : optionButtons) {
        button->render(window);
    }
    backButton->render(window);
}
