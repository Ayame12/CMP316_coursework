#pragma once

#include "GameState.h"

class Level
{
public:
	Level(sf::RenderWindow* hwnd, GameState* gs);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	sf::View view;

	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	//Input* input;
	GameState* gameState;
};

