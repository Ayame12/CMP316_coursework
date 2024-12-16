#pragma once
#include <vector>
#include <map>
#include "MenuObject.h"

class MenuObject;

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

