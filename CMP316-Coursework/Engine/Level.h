#pragma once
#include <map>

#include "GameState.h"
#include "GameObject.h"
#include "AttackObj.h"

class Level
{
public:
	Level();
	~Level();

	void loadLevel(int lvl);
	void switchLevel();

	//std::vector<GameObject> objList;
	std::map<std::string, GameObject*> objList;
	std::map<std::string, GameObject*> playerObjList;
	std::map<int, AttackObj*> attacks;
	std::vector< GameObject*> collidingObj;

private:
	sf::View view;

	// Default variables for level class.
	sf::RenderWindow* window;
	//Input* input;
	GameState* gameState;
	float completion;

	std::map<std::string, GameObject*> nextObjList;
	std::map<std::string, GameObject*> allObj;
	std::vector< GameObject*> nextCollidingObj;

	std::map<std::string, sf::Texture*> textureMap;
	std::map<std::string, sf::Texture*> nextTextureMap;
	std::map<std::string, sf::Texture*> playerTextureMap;
};

