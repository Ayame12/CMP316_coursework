#include "pch.h"
#include "AttackComponent.h"
#include "GameObject.h"
#include "AttackObj.h"


//using the attack enums the appropriate variables from the long list of initialised variables are used to 
//determine the direction, speed, rotation, and general behaviour of an attack
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
			//an attack that will be triggered by a specific object entering its proximity
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
		//attack triggered based on a set timer
		case TIMER:
		{
			if (!fired)
			{
				fired = true;
			}
			canSpawn = false;
			break;
		}
		//attack triggered by player input
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
	//after the attack has been trigered propperties of the attack are calculated
	if (fired)
	{
		//the components searhes for an available attack object in the pool
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
				//a straight projectile will just follow a straight tragectory, either predetermined or controlled by the player
			case PROJECTILE_STRAIGHT:
			{
				switch (dirCon)
				{
					//attack is initialised in the direction of the mouse
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
				//attack direction is based on the arraw keys (like binding of isaac)
				case KEYBOARD:
				{
					direction = sf::Vector2f(0, 0);
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

					float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
					if (magnitude > 0.0f) {
						direction /= magnitude;
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
			//projectile will be initialised with the direction of a target (another game object)
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
				//mele attack will just appear and then dissapear after a timer
				//not goig to lie, i have not done it jutice
				//somehow projectiles are just a lot better
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
			//attack is initialised with the calculated variables
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
