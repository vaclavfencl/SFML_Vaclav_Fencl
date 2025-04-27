#pragma once
#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../buttons/Button.h"
#include "../buttons/BackButton.h"
#include "../buttons/ResumeButton.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class PauseState : public IGameState {
public:
    PauseState(StateHandler& handler, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    sf::RenderWindow& window;
    sf::Font font;
    sf::RectangleShape background;
    sf::Text title;
    std::vector<std::unique_ptr<Button>> buttons;
};

#endif
