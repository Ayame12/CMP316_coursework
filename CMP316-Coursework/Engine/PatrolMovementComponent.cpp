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

        //gets the position of the next target point
        sf::Vector2f target = patrolPoints[currentTargetIndex];

        //substacts own position from target to get direction
        sf::Vector2f direction = target - gameObj->getPosition();

        //pithagoras formula to calulate distance
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        //if distance is larger than 0 
        if (distance > 0.0f) {
            //normalize direction
            direction /= distance;

            //calculate velocity and move object
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

            //briefly dont allow object to move if it has been hit by an attack

            if (!gameObj->hurt)
            {
                //set velosity to be used in other components
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
