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

	for (auto const& it : level.attacks)
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
	sf::Vector2f viewCen = { 0,0 };
	for (auto const& it : level.objList)
	{
		it.second->update(dt);
	}
	for (auto const& it : level.playerObjList)
	{
		it.second->update(dt);
		viewCen += it.second->getPosition();
	}
	for (auto const& it : level.attacks)
	{
		if (it.second->isAlive())
		{
			it.second->update(dt);
		}
	}
	int x = viewCen.x / level.playerObjList.size();
	int y = viewCen.y / level.playerObjList.size();
	view.setCenter(sf::Vector2f(x, y));
	
}

void Scene::render()
{
	window->setView(view);
	for (auto const& it : level.objList)
	{
		window->draw(*it.second);
	}
	for (auto const& it : level.playerObjList)
	{
		window->draw(*it.second);
	}
	for (auto const& it : level.attacks)
	{
		if (it.second->isAlive())
		{
			window->draw(*it.second);
		}
	}

	//level.objList.at("hand");

}

bool checkBoundingBox(GameObject* s1, GameObject* s2)
{
	if (s1->getCollisionBox().left + s1->getCollisionBox().width < s2->getCollisionBox().left)
		return false;
	if (s1->getCollisionBox().left > s2->getCollisionBox().left + s2->getCollisionBox().width)
		return false;
	if (s1->getCollisionBox().top + s1->getCollisionBox().height < s2->getCollisionBox().top)
		return false;
	if (s1->getCollisionBox().top > s2->getCollisionBox().top + s2->getCollisionBox().height)
		return false;

	return true;
}
