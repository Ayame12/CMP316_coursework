#pragma once
#include "GameState.h"
#include "Input.h"
#include "Level.h"
#include <thread>
#include <atomic>

class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in, GameState* gs/*, AudioManager* aud*/);
	~Scene();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	void handleAttackCollisions();
	void handleCharactersCollisions(float dt);
	bool checkBoundingBox(GameObject* s1, GameObject* s2);

	sf::View view;

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	//AudioManager* audio;

	Level level;
	Level* currentLevel;

	void loadLevelInBackground(int levelNumber);
	bool isLevelLoading() const { return loadingLevel; }

private:
	bool loaded2 = false;
	bool showNextLvl = false;
	std::thread levelLoadingThread;
	std::atomic<bool> loadingLevel{ false };
};

