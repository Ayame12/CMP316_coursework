#include "pch.h"
#include "FollowMovementComponent.h"
#include "GameObject.h"

void FollowMovementComponent::handleInput(GameObject* gamgameObjeObject, float dt)
{
	
}

void FollowMovementComponent::update(GameObject* gameObj, float dt)
{
    //gets direction by sustraction current position of the object from the target position
    sf::Vector2f direction = target->getPosition() - gameObj->getPosition();

    //pithagoras formula to calculate distance
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    //if the distance is greater than the threshold
    if (distance > distKept) {
        //normalise direction 
        direction /= distance;

        //calculate velosity
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
        //briefly dont allow object to move if it has been hit by an attack
        if (!gameObj->hurt)
        {
            //i only set the velocity of the object here because it allows me to check what way its moving in other components
            //useful for animation component for example
            gameObj->setVelocity(movement);
            gameObj->move(movement);
        }
    }
    else
    {
        gameObj->setVelocity(sf::Vector2f(0, 0));
    }

}
