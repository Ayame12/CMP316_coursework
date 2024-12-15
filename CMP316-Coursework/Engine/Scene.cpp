#include "pch.h"
#include "Scene.h"
#include <math.h>
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

	if (input->isPressed(sf::Keyboard::Key::P) && !loaded2 && !loadingLevel) {
		loadLevelInBackground(2);
		loaded2 = true; // Flag to prevent duplicate loads
	}

	if (input->isPressed(sf::Keyboard::Key::U) && !showNextLvl && loaded2 && !loadingLevel) {
		level.switchLevel();
		showNextLvl = true;
	}

	for (auto const& it : level.objList)
	{
		if (it.second->isAlive())
		{
			it.second->handleInput(dt);
		}
	}
	for (auto const& it : level.playerObjList)
	{
		if (it.second->isAlive())
		{
			it.second->handleInput(dt);
		}
	}
}

void Scene::update(float dt)
{
	sf::Vector2f viewCen = { 0,0 };
	for (auto const& it : level.objList)
	{
		if (it.second->isAlive())
		{
			it.second->update(dt);
		}
	}
	for (auto const& it : level.playerObjList)
	{
		if (it.second->isAlive())
		{
			it.second->update(dt);
			viewCen += it.second->getPosition();
		}
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

	handleCharactersCollisions(dt);
	handleAttackCollisions();
	
}

void Scene::render()
{
	window->setView(view);
	for (auto const& it : level.objList)
	{
		if (it.second->isAlive())
		{
			window->draw(*it.second);
			/*sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(sf::Vector2f(it.second->getCollisionBox().left, it.second->getCollisionBox().top));
			rectangle.setSize(sf::Vector2f(it.second->getCollisionBox().width, it.second->getCollisionBox().height));
			window->draw(rectangle);*/
		}
	}
	for (auto const& it : level.playerObjList)
	{
		if (it.second->isAlive())
		{
			window->draw(*it.second);
			/*sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(sf::Vector2f(it.second->getCollisionBox().left, it.second->getCollisionBox().top));
			rectangle.setSize(sf::Vector2f(it.second->getCollisionBox().width, it.second->getCollisionBox().height));
			window->draw(rectangle);*/
		}
	}
	for (auto const& it : level.attacks)
	{
		if (it.second->isAlive())
		{
			window->draw(*it.second);
			/*sf::RectangleShape rectangle;
			rectangle.setFillColor(sf::Color::Blue);
			rectangle.setPosition(sf::Vector2f(it.second->getCollisionBox().left, it.second->getCollisionBox().top));
			rectangle.setSize(sf::Vector2f(it.second->getCollisionBox().width, it.second->getCollisionBox().height));
			window->draw(rectangle);*/
		}
		
	}

	//level.objList.at("hand");

}

void Scene::handleAttackCollisions()
{
	for (int j = 0; j <level.attacks.size(); ++j)
	{
		if (level.attacks.at(j)->isAlive())
		{
			for (int i = 0; i < level.collidingObj.size(); ++i)
			{
				if (level.collidingObj.at(i)->isAlive())
				{
					if (checkBoundingBox(level.attacks.at(j), level.collidingObj[i]))
					{
						if (level.collidingObj[i]->IsCharacter())
						{
							if (level.collidingObj[i]->IsPlayer())
							{
								if (!(level.attacks.at(j)->getIsPlayer()))
								{
									level.collidingObj[i]->takeDamage(level.attacks.at(j)->damage);
									level.attacks.at(j)->setAlive(false);
								}
							}
							else
							{
								if (level.attacks.at(j)->getIsPlayer())
								{
									level.collidingObj[i]->takeDamage(level.attacks.at(j)->damage);
									level.attacks.at(j)->setAlive(false);
								}
							}
						}
						else if (level.collidingObj[i]->IsBarrier())
						{
							level.attacks.at(j)->setAlive(false);
						}
					}
				}
			}
		}
	}
}

void Scene::handleCharactersCollisions(float dt)
{
	for (int i = 0; i < level.collidingObj.size(); ++i)
	{
		if (level.collidingObj[i]->isAlive())
		{
			for (int j = i+1; j < level.collidingObj.size(); ++j)
			{
				if (level.collidingObj[j]->isAlive())
				{
					if (checkBoundingBox(level.collidingObj[i], level.collidingObj[j]))
					{
						float moveBy = 0.2;
						if (!level.collidingObj[i]->IsBarrier())
						{
							//moveBy = level.collidingObj[i]->getVelocity().x * dt;
							sf::Vector2f dir = level.collidingObj[i]->getPosition() - level.collidingObj[j]->getPosition();
							if (dir.x < 0)
							{
								level.collidingObj[i]->move(-moveBy, 0);
							}
							else if (dir.x > 0)
							{
								level.collidingObj[i]->move(moveBy, 0);
							}
							//moveBy = level.collidingObj[i]->getVelocity().y * dt;
							if (dir.y < 0)
							{
								level.collidingObj[i]->move(0, -moveBy);
							}
							else if (dir.y > 0)
							{
								level.collidingObj[i]->move(0, moveBy);
							}
						}
						if (!level.collidingObj[j]->IsBarrier())
						{
							sf::Vector2f dir = level.collidingObj[j]->getPosition() - level.collidingObj[i]->getPosition();
							//moveBy = level.collidingObj[j]->getVelocity().x * dt;
							if (dir.x < 0)
							{
								level.collidingObj[j]->move(-moveBy, 0);
							}
							else if (dir.x > 0)
							{
								level.collidingObj[j]->move(moveBy, 0);
							}
							//moveBy = level.collidingObj[i]->getVelocity().y * dt;
							if (dir.y < 0)
							{
								level.collidingObj[j]->move(0, -moveBy);
							}
							else if (dir.y > 0)
							{
								level.collidingObj[j]->move(0, moveBy);
							}
						}
					}
				}
			}
		}
	}
}

bool Scene::checkBoundingBox(GameObject* s1, GameObject* s2)
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

void Scene::loadLevelInBackground(int levelNumber) {
	// If already loading, don't start a new thread
	if (loadingLevel) return;

	loadingLevel = true; // Set the flag

	// Launch a background thread
	levelLoadingThread = std::thread([this, levelNumber]() {
		// Load the level
		level.loadLevel(levelNumber);

		// Switch the level once loading is complete
		//level.switchLevel();

		// Mark loading as complete
		loadingLevel = false;
		});

	// Detach the thread so it runs independently
	levelLoadingThread.detach();
}
