#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
	alive = true;
	input = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::handleInput(float dt)
{
}

void GameObject::update(float dt)
{
}
