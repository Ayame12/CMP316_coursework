#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "AttackObj.h"

void AttackComponent::handleInput(GameObject* gameObj, float dt)
{
	if (!canSpawn)
	{
		timePassed += dt;
	}
	if (timePassed >= coolDown)
	{
		canSpawn = true;
		timePassed = 0;
	}

	if (canSpawn)
	{
		timePassed == 0;
		position = sf::Vector2f(gameObj->getPosition().x + xOffset, gameObj->getPosition().y + yOffset);
		switch (cond)
		{
		case OBJ_PROXIMITY:
		{
			sf::Vector2f targetPos = proxiObj->getPosition();

			float distance = std::sqrt((targetPos.x - position.x) * (targetPos.x - position.x) + (targetPos.y - position.y) * (targetPos.y - position.y));
			if (distance < proximityDistance)
			{
				if (!fired)
				{
					fired = true;
				}
				canSpawn = false;
			}
			break;
		}
		case TIMER:
		{
			if (!fired)
			{
				fired = true;
			}
			canSpawn = false;
			break;
		}
		case PLAYER:
		{
			if (gameObj->input->GetSFKey(control))
			{
				if (!fired)
				{
					fired = true;
				}
				canSpawn = false;
			}
			break;
		}
		case NO_COND:
			break;
		default:
			break;
		}
	}

	if (fired)
	{
		fired = false;
		for (int i = 0; i < allattacks->size(); i++)
		{
			if (!allattacks->at(i)->isAlive())
			{
				index = i;
				found = true;
				break;
			}
		}

		if (found)
		{
			switch (type)
			{
			case PROJECTILE_STRAIGHT:
			{
				switch (dirCon)
				{
				case MOUSE:
				{
					auto siz = gameObj->window->getView().getSize();
					auto mx = gameObj->input->getMouseX();
					auto my = gameObj->input->getMouseY();
					direction = sf::Vector2f(mx - siz.x / 2, my - siz.y / 2);
					float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					direction /= distance;

					rotation += 180 * direction.x + 180 * direction.y;
					break;
				}
				case KEYBOARD:
				{
					direction = sf::Vector2f(0, 0);
					// Determine direction based on input
					if (gameObj->input->isKeyDown(sf::Keyboard::Up)) {
						direction.y -= 1.0f;
					}
					if (gameObj->input->isKeyDown(sf::Keyboard::Down)) {
						direction.y += 1.0f;
					}
					if (gameObj->input->isKeyDown(sf::Keyboard::Left)) {
						direction.x -= 1.0f;
					}
					if (gameObj->input->isKeyDown(sf::Keyboard::Right)) {
						direction.x += 1.0f;
					}

					// Normalize direction to prevent faster diagonal movement
					float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					if (magnitude > 0.0f) {
						direction /= magnitude; // Normalize to unit vector
					}
					break;
				}
				case NO_CONTROL:
					break;
				default:
					break;
				}
				break;
			}
			case PROJECTILE_TARGETED:
			{
				direction = target->getPosition();
				sf::Vector2f d = direction - position;
				
				direction = d;
				float distance = std::sqrt(d.x* d.x + d.y * d.y);
				direction /= distance;

				rotation = 180 * direction.x + 180 * direction.y + initRotation;

			}
				break;
			case MELE:
			{
				speed = 0;
				isMele = true;
			}
				break;
			case NO_ATTACK:
				break;
			default:
				break;
			}
		}
		if (!gameObj->hurt)
		{
			allattacks->at(index)->setTexture(texture);
			allattacks->at(index)->setSize(sf::Vector2f(texture->getSize()));
			allattacks->at(index)->initialize(position, scale, direction, rotation, speed, meleMaxTimer, isMele, gameObj->IsPlayer(), damage);
			allattacks->at(index)->setCollisionBox(0, 0, allattacks->at(index)->getSize().x, allattacks->at(index)->getSize().y);
		}
		isMele = false;
	}		
}

void AttackComponent::update(GameObject* gameObj, float dt)
{
	
}
