#pragma once
#include "Input.h"
#include "Level.h"
#include "Menu.h"
#include <thread>
#include <atomic>
#include "GAME_STATES_ENUM.h"

//my scene is responsible with changing the game state and level and loading new levels in the backround
//scene is also responsible with checking all collisions in the level 

class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in);
	~Scene();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	void handleAttackCollisions();
	void handleCharactersCollisions(float dt);
	bool checkBoundingBox(GameObject* s1, GameObject* s2);

	sf::View view;

	sf::RenderWindow* window;
	Input* input;
	GAME_STATE gameState;

	Level level;
	Menu menu;

	float maxPauseTimer = 0.2;
	float pauseTimer = 0;
	bool pausePressed = false;

	void loadLevelInBackground(int levelNumber);
	bool isLevelLoading() const { return loadingLevel; }

private:
	std::thread levelLoadingThread;
	std::atomic<bool> loadingLevel{ false };
	std::atomic<bool> levelLoaded{ false };

	int currentLevel = 1;
	int loadedLevelNo = 1;
	int maxLevel;
	int enemiesAlive = 0;
	void countEnemies();
};

