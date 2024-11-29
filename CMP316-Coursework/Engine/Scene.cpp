#include "pch.h"
#include "Scene.h"
//#include "Input.h"

Scene::Scene(sf::RenderWindow* hwnd, Input* in, GameState* gs/*, AudioManager* aud*/) 
{
	window = hwnd;
	input = in;
	gameState = gs;
	//audio = aud;

	view = window->getView();
}

Scene::~Scene()
{
}

void Scene::handleInput(float dt)
{
}

void Scene::update(float dt)
{
}

void Scene::render()
{
}
