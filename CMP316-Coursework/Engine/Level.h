#pragma once
#include <map>

#include "GameState.h"
#include "GameObject.h"

class Level
{
public:
	Level();
	~Level();

	void loadLevel(int lvl);
	GameObject getGameObj(int n);

	//std::vector<GameObject> objList;
	std::map<std::string, GameObject*> objList;
private:
	sf::View view;

	// Default variables for level class.
	sf::RenderWindow* window;
	//Input* input;
	GameState* gameState;
	float completion;

	std::map<std::string, sf::Texture*> textureMap;
};

