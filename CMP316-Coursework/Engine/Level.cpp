#include "pch.h"
#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::loadLevel()
{
	GameObject* n = new GameObject;
	objectList.push_back(n);

}

GameObject Level::getGameObj(int n)
{
	return GameObject();
}

