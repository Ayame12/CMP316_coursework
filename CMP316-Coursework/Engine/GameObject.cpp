#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	alive = true;
	input = nullptr;

	setOrigin(0.5, 0.5);
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
