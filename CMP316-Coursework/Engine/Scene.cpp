#include "pch.h"
#include "Scene.h"
#include <math.h>
#include <fstream>

Scene::Scene(sf::RenderWindow* hwnd, Input* in) 
{
	window = hwnd;
	input = in;
	gameState = GAME_STATE::MENU;

	view = window->getView();
	level.loadLevel(1);
	level.switchLevel();

	std::ifstream inn;
	inn.open("../LoadingFiles/fin");
	std::string str;
	inn >> str;
	inn.close();
	maxLevel = stoi(str);

	for (int i = 0; i < menu.mainMenuObj.size(); i++)
	{
		menu.mainMenuObj[i]->setWindow(window);
		menu.mainMenuObj[i]->setInput(input);
		menu.mainMenuObj[i]->setLevelAndGS(&level, &gameState);
	}

	for (int i = 0; i < menu.pauseMenuObj.size(); i++)
	{
		menu.pauseMenuObj[i]->setWindow(window);
		menu.pauseMenuObj[i]->setInput(input);
		menu.pauseMenuObj[i]->setLevelAndGS(&level, &gameState);
	}

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
}

Scene::~Scene()
{
}

void Scene::handleInput(float dt)
{
	if (pausePressed)
	{
		pauseTimer += dt;
	}
	if (pauseTimer >= maxPauseTimer)
	{
		pauseTimer = 0;
	}
	if (pauseTimer == 0)
	{
		pausePressed = false;
	}

	switch (gameState)
	{
	case MENU:
	{
		for (int i = 0; i < menu.mainMenuObj.size(); i++)
		{
			menu.mainMenuObj[i]->handleInput(dt);
		}
		break;
	}
	case PAUSE:
	{
		if (input->isPressed(sf::Keyboard::Key::Escape) && !pausePressed)
		{
			gameState = GAME_STATE::LEVEL;
			pausePressed = true;
		}
		for (int i = 0; i < menu.pauseMenuObj.size(); i++)
		{
			menu.pauseMenuObj[i]->handleInput(dt);
		}
		break;
	}
	case LEVEL:
	{
		if (input->isPressed(sf::Keyboard::Key::Escape) && !pausePressed)
		{
			gameState = GAME_STATE::PAUSE;
			pausePressed = true;
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
		break;
	}
	default:
		break;
	}
}

void Scene::update(float dt)
{
	sf::Vector2f viewCen = { 0,0 };
	switch (gameState)
	{
	case MENU:
	{
		viewCen = menu.menuBg->getOrigin();
		for (int i = 0; i < menu.mainMenuObj.size(); i++)
		{
			menu.mainMenuObj[i]->update(dt);
		}
		break;
	}
	case PAUSE:
	{
		viewCen = menu.pauseBg->getOrigin();
		for (int i = 0; i < menu.pauseMenuObj.size(); i++)
		{
			menu.pauseMenuObj[i]->update(dt);
		}
		break;
	}
	case LEVEL:
	{
		countEnemies();
		int prevLLev = currentLevel;

		if (enemiesAlive <= 2 && !loadingLevel && !levelLoaded) {
			if (currentLevel != maxLevel)
			{
				loadLevelInBackground(currentLevel + 1);
			}
			else 
			{
				loadLevelInBackground(1);
			}
		}

		if (enemiesAlive == 0) {
			if (currentLevel != maxLevel) {
				if (!isLevelLoading() && levelLoaded) {
					level.switchLevel();
					for (auto const& it : level.objList)
					{
						it.second->setWindow(window);
						it.second->setInput(input);
					}
					currentLevel++;
					levelLoaded = false;
				}
			}
			else 
			{
				gameState = GAME_STATE::MENU;
				currentLevel = 1;

				if (!loadingLevel && !levelLoaded) {
					loadLevelInBackground(1);
				}

				if (!isLevelLoading() && levelLoaded) {
					level.switchLevel();
					levelLoaded = false;
					for (auto const& it : level.objList)
					{
						it.second->setWindow(window);
						it.second->setInput(input);
					}
				}
			}
			
		}

		if (prevLLev != currentLevel)
		{
			std::cout << currentLevel << std::endl;
		}


		viewCen = { 0,0 };
		for (auto const& it : level.objList)
		{
			if (it.second->isAlive())
			{
				it.second->update(dt);
			}
		}
		int playersAlive = 0;
		for (auto const& it : level.playerObjList)
		{
			if (it.second->isAlive())
			{
				playersAlive++;
				it.second->update(dt);
				viewCen += it.second->getPosition();
			}
		}
		if (playersAlive == 0)
		{
			if (!loadingLevel)
			{
				gameState = GAME_STATE::MENU;
				currentLevel = 1;
				loadedLevelNo = false;
				loadingLevel = false;
				loadLevelInBackground(1);
				break;
			}
		}
		for (auto const& it : level.attacks)
		{
			if (it.second->isAlive())
			{
				it.second->update(dt);
			}
		}
		handleCharactersCollisions(dt);
		handleAttackCollisions();

		viewCen.x = viewCen.x / level.playerObjList.size();
		viewCen.y = viewCen.y / level.playerObjList.size();

		break;
	}
	default:
		break;
	}	
	view.setCenter(viewCen);
	
}

void Scene::render()
{
	window->setView(view);

	switch (gameState)
	{
	case MENU:
	{
		window->draw(*menu.menuBg);
		window->draw(menu.menuBg->text);
		for (int i = 0; i < menu.mainMenuObj.size(); i++)
		{
			window->draw(*menu.mainMenuObj[i]);
			window->draw(menu.mainMenuObj[i]->text);
		}
		break;
	}
	case PAUSE:
	{
		window->draw(*menu.pauseBg);
		window->draw(menu.pauseBg->text);
		for (int i = 0; i < menu.pauseMenuObj.size(); i++)
		{
			window->draw(*menu.pauseMenuObj[i]);
			window->draw(menu.pauseMenuObj[i]->text);
		}
		break;
	}
	case LEVEL:
	{
		for (auto const& it : level.objList)
		{
			if (it.second->isAlive())
			{
				window->draw(*it.second);
			}
		}
		for (auto const& it : level.playerObjList)
		{
			if (it.second->isAlive())
			{
				window->draw(*it.second);
			}
		}
		for (auto const& it : level.attacks)
		{
			if (it.second->isAlive())
			{
				window->draw(*it.second);
			}

		}
		for (auto const& it : level.playerObjList)
		{
			if (it.second->isAlive())
			{
				for (int j = 0; j < it.second->getHealth(); j++)
				{

					sf::RectangleShape rectangle;
					rectangle.setPosition(sf::Vector2f(view.getCenter().x - it.second->hpPos.x + (it.second->hpTexture->getSize().x * it.second->hpSca.x * j * 1.5), view.getCenter().y - it.second->hpPos.y));
					rectangle.setSize(sf::Vector2f(it.second->hpTexture->getSize().x, it.second->hpTexture->getSize().y));
					rectangle.setTexture(it.second->hpTexture);
					rectangle.setScale(it.second->hpSca);
					window->draw(rectangle);
				}
			}
		}

		break;
	}
	default:
		break;
	}
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
									if (!level.collidingObj[i]->isAlive())
									{
										enemiesAlive--;
									}
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
							sf::Vector2f dir = level.collidingObj[i]->getPosition() - level.collidingObj[j]->getPosition();
							if (dir.x < 0)
							{
								level.collidingObj[i]->move(-moveBy, 0);
							}
							else if (dir.x > 0)
							{
								level.collidingObj[i]->move(moveBy, 0);
							}
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
							if (dir.x < 0)
							{
								level.collidingObj[j]->move(-moveBy, 0);
							}
							else if (dir.x > 0)
							{
								level.collidingObj[j]->move(moveBy, 0);
							}
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
	if (loadingLevel) return;
	loadingLevel = true;

	levelLoadingThread = std::thread([this, levelNumber]() {
		level.loadLevel(levelNumber);
		levelLoaded = true;
		loadingLevel = false;
		});

	levelLoadingThread.detach();
}

void Scene::countEnemies()
{
	enemiesAlive = 0;
	for (int i = 0; i < level.collidingObj.size(); i++)
	{
		if (level.collidingObj[i]->IsCharacter() && !level.collidingObj[i]->IsPlayer() && !level.collidingObj[i]->IsBarrier() && level.collidingObj[i]->isAlive())
		{
			enemiesAlive++;
		}
	}
}