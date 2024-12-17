#include "pch.h"
#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "Input.h"

void PlayerMovementComponent::handleInput(GameObject* gameObj, float dt)
{
    sf::Vector2f direction = { 0, 0 };

    //based on the input the direction of movement will be altered
    //this prevents situations where one input overpowers the othr

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

    //calculate magnitude and normalize direction
    //this is done so that the object doesnt move quicker on a diagonal
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

    //briefly dont allow object to move if it has been hit by an attack
    if (!gameObj->hurt)
    {
        gameObj->setVelocity(direction * speed);
    }    
}

void PlayerMovementComponent::update(GameObject* gameObj, float dt)
{
    //briefly dont allow object to move if it has been hit by an attack
    // 
    //probably not necessary to check this twice but it helps prevent situations when something else might
    //be setting the velocity of the object other than a movement component (collision response as an example)
    if (!gameObj->hurt)
    {
        gameObj->move(gameObj->getVelocity() * dt);
    }    
}