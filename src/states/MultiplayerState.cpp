#include "MultiplayerState.h"
#include "MenuState.h"
#include "MpGameState.h"
#include "../buttons/HostButton.h"
#include "../buttons/ConnectButton.h"
#include <iostream>

MultiplayerState::MultiplayerState(StateHandler& handler, sf::RenderWindow& win)
    : stateHandler(handler), window(win)
{
    font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf");

    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(200.f, 100.f);
    statusText.setString("Select role:");

    buttons.push_back(std::make_unique<HostButton>(
        sf::Vector2f(200, 60), sf::Vector2f(300, 200), font,
        [this]() { onHostPressed(); }
    ));

    buttons.push_back(std::make_unique<ConnectButton>(
        sf::Vector2f(200, 60), sf::Vector2f(300, 300), font,
        [this]() { onConnectPressed(); }
    ));
}

void MultiplayerState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
            for (auto& button : buttons)
                if (button->isMouseOver(window))
                    button->onClick();
        }
    }
}

void MultiplayerState::update(float dt) {
    for (auto& button : buttons)
        button->update(window);
}

void MultiplayerState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(statusText);
    for (auto& button : buttons)
        button->render(window);
}

void MultiplayerState::onHostPressed() {
    std::cout << "Switching to MpGameState as Host...\n";
    stateHandler.changeState(std::make_shared<MpGameState>(stateHandler, window, true));
}

void MultiplayerState::onConnectPressed() {
    std::cout << "Switching to MpGameState as Client...\n";
    stateHandler.changeState(std::make_shared<MpGameState>(stateHandler, window, false));
}
