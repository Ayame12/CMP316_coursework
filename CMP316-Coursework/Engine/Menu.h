#pragma once
#include <vector>
#include <map>
#include "MenuObject.h"

class MenuObject;

//holds all of the objects present in a menu and is able to load them from a txt file

class Menu
{
public:
	Menu();
	~Menu();

	MenuObject* menuBg;
	MenuObject* pauseBg;
	std::vector<MenuObject*> mainMenuObj;
	std::vector<MenuObject*> pauseMenuObj;

private:
	std::map<std::string, sf::Texture*> alltex;
	void loadMenus();

};

