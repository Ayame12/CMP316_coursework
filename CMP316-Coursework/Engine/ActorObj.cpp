#include "pch.h"
#include "ActorObj.h"

ActorObj::ActorObj()
{
	isPlayer = false;
	controlls.push_back(1);
}

ActorObj::~ActorObj()
{
}

void ActorObj::handleInput(float dt)
{
}

void ActorObj::update(float dt)
{
}

void ActorObj::setMovementControlls(int up, int dowm, int left, int right)
{
}
