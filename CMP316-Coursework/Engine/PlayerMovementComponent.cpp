#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "Input.h"

void PlayerMovementComponent::handleInput(GameObject* gameObj, float dt)
{
    sf::Vector2f direction = { 0, 0 };

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

    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0.0f) {
        direction /= magnitude;
    }

    if (direction.x < 0)
    {
        gameObj->setFlipped(true);
    }
    else
    {
        gameObj->setFlipped(false);
    }

    if (!gameObj->hurt)
    {
        gameObj->setVelocity(direction * speed);
    }    
}

void PlayerMovementComponent::update(GameObject* gameObj, float dt)
{
    if (!gameObj->hurt)
    {
        gameObj->move(gameObj->getVelocity() * dt);
    }    
}