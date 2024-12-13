#include "pch.h"
#include "FollowMovementComponent.h"
#include "GameObject.h"

void FollowMovementComponent::handleInput(GameObject* gamgameObjeObject, float dt)
{
	
}

void FollowMovementComponent::update(GameObject* gameObj, float dt)
{
	//sf::Vector2f direction = target->getPoint;
    // Calculate the direction vector to the target
    sf::Vector2f direction = target->getPosition() - gameObj->getPosition();

    // Compute the distance to the target
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > distKept) {
        // Normalize the direction vector
        direction /= distance;

        // Move towards the target, limited by speed and delta time
        sf::Vector2f velocity = direction * speed;
        sf::Vector2f movement = velocity * dt;

        // Ensure the object doesn't overshoot the target
        if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
            movement = target->getPosition() - gameObj->getPosition();
        }

        gameObj->setVelocity(movement);
        gameObj->move(movement);
    }
    else
    {
        gameObj->setVelocity(sf::Vector2f(0, 0));
    }

}
