#include "pch.h"
#include "ActorObj.h"

ActorObj::ActorObj()
{
	isPlayer = false;
	input = nullptr;
	controlls.push_back(input.GetSFKey(0));
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
