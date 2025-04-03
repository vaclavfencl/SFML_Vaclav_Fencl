#include "Game.h"

Game::Game()
    : window(sf::VideoMode(800, 600), "Snake Game"), ball(), paddle(30.f,50.f), paddleAi(750.f,50.f) {
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
    paddle.updatePlayer(deltaTime);
    paddleAi.updateAI(deltaTime, ball);
    ball.update(deltaTime);
    if (ball.getPosition().y < 0.f || ball.getPosition().y + 40.f > 600.f) {
        ball.bounceY();
    }
    if (ball.getPosition().x -18.f < paddle.getPosition().x || ball.getPosition().x +15.f > paddleAi.getPosition().x) {
        ball.reset();
    }

    if (ball.getBounds().intersects(paddle.getBounds())) {
        ball.bounceX();
    }

    if (ball.getBounds().intersects(paddleAi.getBounds())) {
        ball.bounceX();
    }

}

void Game::render() {
    window.clear();
    paddle.render(window);
    paddleAi.render(window);
    ball.render(window);
    window.display();
}
