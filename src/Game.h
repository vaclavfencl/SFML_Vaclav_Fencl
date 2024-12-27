#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

class Game {
public:
    Game();
    void run();

private:
    sf::Clock clock;
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    Entity apple;  
};

#endif
