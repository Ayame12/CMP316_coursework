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
			sf::Vector2f targetPos = target->getPosition();

			float distance = std::sqrt((targetPos.x - position.x) * (targetPos.x - position.x) + (targetPos.y - position.y) * (targetPos.y - position.y));
			if (distance < targetMinDist)
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
					direction = sf::Vector2f(gameObj->input->getMouseX() - gameObj->getPosition().x, gameObj->input->getMouseY() - gameObj->getPosition().y);

					float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					direction /= distance;

					rotation += 180 * direction.x + 180 * direction.y;
					break;
				}
				case KEYBOARD:
					//in progress
					break;
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

				float distance = std::sqrt((direction.x - position.x) * (direction.x - position.x) + (direction.y - position.y) * (direction.y - position.y));
				direction /= distance;

				rotation += 180 * direction.x + 180 * direction.y;
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
		allattacks->at(index)->setTexture(texture);
		allattacks->at(index)->setSize(sf::Vector2f(20,20));
		allattacks->at(index)->initialize(position, scale, direction, rotation, speed, meleMaxTimer, isMele);
		isMele = false;
	}		
}

void AttackComponent::update(GameObject* gameObj, float dt)
{
	
}
