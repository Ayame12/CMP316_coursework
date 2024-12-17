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

        sf::Vector2f target = patrolPoints[currentTargetIndex];

        sf::Vector2f direction = target - gameObj->getPosition();

        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance > 0.0f) {
            direction /= distance;

            sf::Vector2f velocity = direction * speed;
            sf::Vector2f movement = velocity * dt;

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

            if (!gameObj->hurt)
            {
                gameObj->setVelocity(movement);
                gameObj->move(movement);
            }
        }
        else
        {
            gameObj->setVelocity(sf::Vector2f(0, 0));
        }

        if (distance < 1.0f) { 
            currentTargetIndex = (currentTargetIndex + 1) % patrolPoints.size();
        }
    }
}
