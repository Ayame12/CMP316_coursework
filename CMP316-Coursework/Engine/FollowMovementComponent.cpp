#include "pch.h"
#include "FollowMovementComponent.h"
#include "GameObject.h"

void FollowMovementComponent::handleInput(GameObject* gamgameObjeObject, float dt)
{
	
}

void FollowMovementComponent::update(GameObject* gameObj, float dt)
{
    sf::Vector2f direction = target->getPosition() - gameObj->getPosition();

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > distKept) {
        direction /= distance;

        sf::Vector2f velocity = direction * speed;
        sf::Vector2f movement = velocity * dt;

        if (std::sqrt(movement.x * movement.x + movement.y * movement.y) > distance) {
            movement = target->getPosition() - gameObj->getPosition();
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

}
