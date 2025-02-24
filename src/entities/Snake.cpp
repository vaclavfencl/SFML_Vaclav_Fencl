#include "Snake.h"

Snake::Snake()
    : direction(0.f, 1.f),      // Start moving downward
    moveDelay(0.2f),          // Move every 0.2 seconds
    timeSinceLastMove(0.f),
    gridStep(60.f),           // Distance between segments (60.f)
    blockSize(50.f)           // Each snake segment is 50.f in size
{
    initializeSnake();
}

// Initialize snake with 4 segments starting at a given position
void Snake::initializeSnake() {
    segments.clear();

    // Reset the snake's movement direction to default (downward)
    direction = sf::Vector2f(0.f, 1.f);

    // Let the head start at (250, 250)
    Segment head;
    head.position = sf::Vector2f(250.f, 250.f);
    head.direction = direction;
    segments.push_back(head);

    // Create three additional segments. Each is placed gridStep units behind the previous one.
    for (int i = 1; i < 4; i++) {
        Segment seg;
        seg.position = segments[i - 1].position - head.direction * gridStep;
        seg.direction = head.direction;
        segments.push_back(seg);
    }
}

void Snake::handleInput() {
    sf::Vector2f newDirection = direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        newDirection = sf::Vector2f(0.f, -1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        newDirection = sf::Vector2f(0.f, 1.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        newDirection = sf::Vector2f(-1.f, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        newDirection = sf::Vector2f(1.f, 0.f);
    }

    // Allow change only if the new direction is perpendicular to the current one.
    if (direction.x == 0 && newDirection.x != 0) {
        direction = newDirection;
    }
    else if (direction.y == 0 && newDirection.y != 0) {
        direction = newDirection;
    }
}

void Snake::update(float deltaTime) {
    handleInput();
    timeSinceLastMove += deltaTime;

    if (timeSinceLastMove >= moveDelay) {
        // Update body segments from tail to head.
        // Each segment copies the position and direction of the segment in front.
        for (int i = segments.size() - 1; i > 0; i--) {
            segments[i] = segments[i - 1];
        }

        // Update the head segment: set its direction from current input and move it by gridStep.
        segments[0].direction = direction;
        segments[0].position += direction * gridStep;

        // Check if head is out of bounds (running outta room).
        sf::Vector2f headPos = segments[0].position;
        if (headPos.x < 0 || headPos.y < 0 ||
            headPos.x + blockSize > 800 || headPos.y + blockSize > 600)
        {
            // Reset the game.
            initializeSnake();
            timeSinceLastMove = 0.f;
            return;
        }

        // Check for self-collision (touching its own body).
        for (size_t i = 1; i < segments.size(); i++) {
            if (segments[i].position == headPos) {
                // Reset the game.
                initializeSnake();
                timeSinceLastMove = 0.f;
                return;
            }
        }

        // Reset the timer after a successful move.
        timeSinceLastMove = 0.f;
    }
}

void Snake::render(sf::RenderWindow& window) {
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(blockSize, blockSize));
    rect.setFillColor(sf::Color::Green);

    for (const auto& seg : segments) {
        rect.setPosition(seg.position);
        window.draw(rect);
    }
}
