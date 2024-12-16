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

void GameObject::handleInput(float dt)
{
	for (const auto& component : components) {
		component->handleInput(this, dt);
	}
}

void GameObject::update(float dt)
{
	/*velocity = speed;
	move(velocity * dt);*/
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
		health -= dmg;
	}
	if (health <= 0)
	{
		alive = false;
	}
}
