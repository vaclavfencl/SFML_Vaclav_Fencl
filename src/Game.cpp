#include "Game.h"

Game::Game(sf::RenderWindow& window)
    : window(window), ball(), paddle(30.f, 50.f, screenHeight), paddleAi(750.f, 50.f, screenHeight)
{
    if (!font.loadFromFile("Thirdparty/fonts/Roboto-Light.ttf")) {
        // Handle error
    }

    scoreText1.setFont(font);
    scoreText1.setCharacterSize(30);
    scoreText1.setFillColor(sf::Color::White);
    scoreText1.setPosition(200.f, 20.f);

    scoreText2.setFont(font);
    scoreText2.setCharacterSize(30);
    scoreText2.setFillColor(sf::Color::White);
    scoreText2.setPosition(550.f, 20.f);
}
/*
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
}*/

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    paddle.updatePlayer(deltaTime);
    paddleAi.updateAI(deltaTime, ball);
    ball.update(deltaTime);
    if (ball.getPosition().y < 0.f || ball.getPosition().y + 40.f > screenHeight) {
        ball.bounceY();
    }
    if (ball.getPosition().x + ball.radius*2 >= screenWidth) {
        score1 += 1;
        ball.reset();
    }
    else if (ball.getPosition().x <= 0.f) {
        score2 += 1;
        ball.reset();
    }

    if (ball.getBounds().intersects(paddle.getBounds())) {
        if (ball.getDirection().x < 0 && ball.bounced != 1) { // moving toward player paddle
            // Move ball to the edge of the paddle
            ball.setPosition(paddle.getPosition().x + paddle.getSize().x + 0.1f, ball.getPosition().y);

            float paddleCenterY = paddle.getPosition().y + paddle.getSize().y / 2.f;
            float ballCenterY = ball.getPosition().y + ball.radius;
            float diff = ballCenterY - paddleCenterY;

            float normalized = diff / (paddle.getSize().y / 2.f);
            ball.setDirection(normalized);
            ball.bounceX();
            ball.bounced = 1;
        }
    }



    if (ball.getBounds().intersects(paddleAi.getBounds())) {
        if (ball.getDirection().x > 0 && ball.bounced != 0) { // ball is moving right
            // Move ball just left of the paddle
            ball.setPosition(paddleAi.getPosition().x - ball.radius * 2.f - 0.1f, ball.getPosition().y);

            float paddleCenterY = paddleAi.getPosition().y + paddleAi.getSize().y / 2.f;
            float ballCenterY = ball.getPosition().y + ball.radius;
            float diff = ballCenterY - paddleCenterY;

            float normalized = diff / (paddleAi.getSize().y / 2.f);
            ball.setDirection(normalized);
            ball.bounceX();
            ball.bounced = 0;
        }
    }




    scoreText1.setString(std::to_string(score1));
    scoreText2.setString(std::to_string(score2));
}

void Game::render() {
    window.clear();
    paddle.render(window);
    paddleAi.render(window);
    ball.render(window);
    window.draw(scoreText1);
    window.draw(scoreText2);
}
