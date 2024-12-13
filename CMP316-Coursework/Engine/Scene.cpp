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
	level.loadLevel(1);
	level.switchLevel();

	for (auto const& it : level.playerObjList)
	{
		it.second->setWindow(window);
		it.second->setInput(input);
	}

	for (auto const& it : level.objList)
	{
		it.second->setWindow(window);
		it.second->setInput(input);
	}
	/*sf::Texture tex;
	tex.loadFromFile("res/image.png");
	level.objList[0].setTexture(&tex);*/
}

Scene::~Scene()
{
}

void Scene::handleInput(float dt)
{
	for (auto const& it : level.objList)
	{
		it.second->handleInput(dt);
	}
	for (auto const& it : level.playerObjList)
	{
		it.second->handleInput(dt);
	}
}

void Scene::update(float dt)
{
	for (auto const& it : level.objList)
	{
		it.second->update(dt);
	}
	for (auto const& it : level.playerObjList)
	{
		it.second->update(dt);
	}
}

void Scene::render()
{
	//this is how i used to call draw when objects were in a vector
	//window->draw(level.objList[0]);

	for (auto const& it : level.objList)
	{
		window->draw(*it.second);
	}
	for (auto const& it : level.playerObjList)
	{
		window->draw(*it.second);
	}

	//level.objList.at("hand");

}
