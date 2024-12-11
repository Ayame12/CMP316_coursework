#pragma once
#include "GameState.h"
#include "Input.h"
#include "Level.h"

class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in, GameState* gs/*, AudioManager* aud*/);
	~Scene();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	sf::View view;

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	//AudioManager* audio;

	Level level;
	Level* currentLevel;
};

