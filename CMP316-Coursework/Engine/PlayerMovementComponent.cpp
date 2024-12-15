#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "Input.h"

void PlayerMovementComponent::handleInput(GameObject* gameObj, float dt)
{
    sf::Vector2f direction = { 0, 0 };

    // Determine direction based on input
    if (gameObj->input->isKeyDown(controlls[0])) {
        direction.y -= 1.0f;
    }
    if (gameObj->input->isKeyDown(controlls[1])) {
        direction.y += 1.0f;
    }
    if (gameObj->input->isKeyDown(controlls[2])) {
        direction.x -= 1.0f;
    }
    if (gameObj->input->isKeyDown(controlls[3])) {
        direction.x += 1.0f;
    }

    // Normalize direction to prevent faster diagonal movement
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0.0f) {
        direction /= magnitude; // Normalize to unit vector
    }

    if (direction.x < 0)
    {
        gameObj->setFlipped(true);
    }
    else
    {
        gameObj->setFlipped(false);
    }

    // Scale by speed
    gameObj->setVelocity(direction * speed);
}

void PlayerMovementComponent::update(GameObject* gameObj, float dt)
{
    gameObj->move(gameObj->getVelocity() * dt);
}