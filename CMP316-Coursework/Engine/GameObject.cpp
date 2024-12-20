#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	alive = true;
	input = nullptr;

	setOrigin(0, 0);
	setSize(sf::Vector2f(1, 1));
}

GameObject::~GameObject()
{
}

//each game object handles input and updates the components, code inside the components alter the object accordingly

void GameObject::handleInput(float dt)
{
	for (const auto& component : components) {
		component->handleInput(this, dt);
	}
}

void GameObject::update(float dt)
{
	for (const auto& component : components) {
		component->update(this, dt);
	}
}

sf::FloatRect GameObject::getCollisionBox() 
{
	return sf::FloatRect(collisionBox.left + getPosition().x - getOrigin().x, collisionBox.top + getPosition().y - getOrigin().y, collisionBox.width, collisionBox.height);
}

void GameObject::takeDamage(int dmg)
{
	if (isChar)
	{
		hurt = true;
		health -= dmg;
	}
	if (health <= 0)
	{
		alive = false;
	}
}
