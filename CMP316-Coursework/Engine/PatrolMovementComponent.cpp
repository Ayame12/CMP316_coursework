#include "pch.h"
#include "PatrolMovementComponent.h"
#include "GameObject.h"

void PatrolMovementComponent::handleInput(GameObject* gameobj, float dt)
{
}

void PatrolMovementComponent::update(GameObject* gameObj, float dt)
{
    {
        if (patrolPoints.empty()) return;

        // Get the current target point
        sf::Vector2f target = patrolPoints[currentTargetIndex];

        // Calculate the direction vector to the target
        sf::Vector2f direction = target - gameObj->getPosition();

        // Compute the distance to the target
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0.0f) {
            // Normalize the direction vector
            direction /= distance;

            // Move towards the target, limited by speed and delta time
            sf::Vector2f velocity = direction * speed;
            sf::Vector2f movement = velocity * dt;

            // Ensure the object doesn't overshoot the target
            if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
                movement = target - gameObj->getPosition();
            }

            if (movement.x < 0)
            {
                gameObj->setFlipped(true);
            }
            else
            {
                gameObj->setFlipped(false);
            }

            gameObj->setVelocity(movement);
            gameObj->move(movement);
        }
        else
        {
            gameObj->setVelocity(sf::Vector2f(0, 0));
        }

        // Check if we've reached the target
        if (distance < 1.0f) { // Threshold for "reaching" a point
            currentTargetIndex = (currentTargetIndex + 1) % patrolPoints.size(); // Loop to next point
        }
    }
}
