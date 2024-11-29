#pragma once

#include "GameState.h"
#include "GameObject.h"

class Level
{
public:
	Level();
	~Level();

	void loadLevel();
	GameObject getGameObj(int n);


private:
	sf::View view;

	// Default variables for level class.
	sf::RenderWindow* window;
	//Input* input;
	GameState* gameState;
	float completion;

	std::vector<GameObject> objectList;
};

