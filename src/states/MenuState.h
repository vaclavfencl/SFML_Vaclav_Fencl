#pragma once
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "../core/IGameState.h"
#include "../core/StateHandler.h"
#include "../core/TextureManager.h"
#include "../buttons/Button.h"
#include "../buttons/PlayButton.h"
#include "../buttons/SettingsButton.h"
#include "../buttons/ExitButton.h"

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class MenuState : public IGameState {
public:
    MenuState(StateHandler& handler, sf::RenderWindow& window);


    void handleInput(sf::RenderWindow& window) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;

private:
    StateHandler& stateHandler;
    sf::Font font;
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<Button>> buttons;
    sf::Sprite background;

};

#endif
