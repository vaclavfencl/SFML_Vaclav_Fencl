#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Snake Game"), apple() {
    // Initialization code here
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
        // Handle input here
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    apple.update(deltaTime);  
}

void Game::render() {
    window.clear();
    apple.render(window);  // Draw the snake
    window.display();
}
