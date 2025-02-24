#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Snake Game"), apple(), snake() {
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    apple.update(deltaTime);  
    snake.update(deltaTime);  
}

void Game::render() {
    window.clear();
    apple.render(window);  
    snake.render(window);  
    window.display();
}
