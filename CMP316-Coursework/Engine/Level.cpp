#include "pch.h"
#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, GameState* gs)
{
	window = hwnd;
	gameState = gs;
}

Level::~Level()
{
}

void Level::handleInput(float dt)
{
}

void Level::update(float dt)
{
}

void Level::render()
{
}

void Level::beginDraw()
{
}

void Level::endDraw()
{
}
