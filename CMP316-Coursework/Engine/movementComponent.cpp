#include "pch.h"
#include "movementComponent.h"
#include "GameObject.h"
#include "Input.h"

void MovementComponent::handleInput(GameObject* gameObject, float dt)
{
    sf::Vector2f direction = { 0, 0 };

    // Determine direction based on input
    if (gameObject->input->isKeyDown(sf::Keyboard::W)) {
        direction.y -= 1.0f;
    }
    if (gameObject->input->isKeyDown(sf::Keyboard::S)) {
        direction.y += 1.0f;
    }
    if (gameObject->input->isKeyDown(sf::Keyboard::A)) {
        direction.x -= 1.0f;
    }
    if (gameObject->input->isKeyDown(sf::Keyboard::D)) {
        direction.x += 1.0f;
    }

    // Normalize direction to prevent faster diagonal movement
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0.0f) {
        direction /= magnitude; // Normalize to unit vector
    }

    // Scale by speed
    velocity = direction * speed;

    /*if (gameObject->input->isKeyDown(controlls[0]) && gameObject->input->isKeyDown(controlls[1]))
    {
        velocity.y = 0;
    }
    else if (gameObject->input->isKeyDown(controlls[0])) {
        velocity.y = -speed;
    }
    else if (gameObject->input->isKeyDown(controlls[1])) {
        velocity.y = speed;
    }
    else {
        velocity.y = 0;
    }

    if (gameObject->input->isKeyDown(controlls[2]) && gameObject->input->isKeyDown(controlls[3]))
    {
        velocity.x = 0;
    }
    else if (gameObject->input->isKeyDown(controlls[2])) {
        velocity.x = -speed;
    }
    else if (gameObject->input->isKeyDown(controlls[3])) {
        velocity.x = speed;
    }
    else {
        velocity.x = 0;
    }

    if (velocity.x != 0 && velocity.y != 0)
    {
        velo
    }*/
}

void MovementComponent::update(GameObject* gameObject, float dt)
{
    gameObject->move(velocity * dt);
}

// Example: Handle input to change velocity
        /*if (gameObject->input->isKeyDown(sf::Keyboard::W)) {
            velocity.y = -speed;
        }
        else if (gameObject->input->isKeyDown(sf::Keyboard::S)) {
            velocity.y = speed;
        }
        else {
            velocity.y = 0;
        }

        if (gameObject->input->isKeyDown(sf::Keyboard::A)) {
            velocity.x = -speed;
        }
        else if (gameObject->input->isKeyDown(sf::Keyboard::D)) {
            velocity.x = speed;
        }
        else {
            velocity.x = 0;
        }*/

//
//movementComponent::movementComponent(GameObject* o)
//{
//	obj = o;
//}
//
//void movementComponent::handleImput()
//{
//	switch (moveType)
//	{
//	case STATIONARY:
//		break;
//	case PATROOL:
//		break;
//	case FOLLOW:
//		break;
//	case PLAYER_CONTROL:
//		ControlledMovement();
//		break;
//	default:
//		break;
//	}
//}
//
//void movementComponent::update()
//{
//
//}
//
//void movementComponent::ControlledMovement()
//{
//	//up && down
//	if (obj->input->GetSFKey(controlls[0]) && obj->input->GetSFKey(controlls[1]))
//	{
//		obj->setVelocity(sf::Vector2f(obj->getVelocity().x, 0));
//	}
//	//up
//	else if (obj->input->GetSFKey(controlls[0]))
//	{
//		obj->setVelocity(sf::Vector2f(obj->getVelocity().x, obj->getSpeed().y));
//	}
//	//down
//	else if (obj->input->GetSFKey(controlls[1]))
//	{
//		obj->setVelocity(sf::Vector2f(obj->getVelocity().x, -obj->getSpeed().y));
//	}
//	//neither
//	else
//	{
//		obj->setVelocity(sf::Vector2f(obj->getVelocity().x, 0));
//	}
//
//	//left && right
//	if (obj->input->GetSFKey(controlls[2]) && obj->input->GetSFKey(controlls[3]))
//	{
//		obj->setVelocity(sf::Vector2f(0, obj->getVelocity().y));
//	}
//	//left
//	else if (obj->input->GetSFKey(controlls[2]))
//	{
//		obj->setVelocity(sf::Vector2f(-obj->getSpeed().x, obj->getVelocity().y));
//	}
//	//right
//	else if (obj->input->GetSFKey(controlls[3]))
//	{
//		obj->setVelocity(sf::Vector2f(obj->getSpeed().x, obj->getVelocity().y));
//	}
//	//neither
//	else
//	{
//		obj->setVelocity(sf::Vector2f(0, obj->getVelocity().y));
//	}
//}