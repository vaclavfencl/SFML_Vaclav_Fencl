#pragma once
#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../Entity.h"

class Snake : public Entity {
public:
    Snake();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
    void handleInput() override;

private:
    // Structure representing a single segment of the snake.
    struct Segment {
        sf::Vector2f position;
        sf::Vector2f direction;
    };

    std::vector<Segment> segments;  // List of segments (head is segments[0])
    sf::Vector2f direction;         // Current head direction (only cardinal directions allowed)

    // Timing for grid-based movement.
    float moveDelay;                // Time interval between moves.
    float timeSinceLastMove;        // Accumulates elapsed time since last move.

    const float gridStep;           // Distance to move per update (60.f).
    const float blockSize;          // Size of each snake segment (50.f).

    // Resets the snake to its initial state.
    void initializeSnake();
};

#endif
