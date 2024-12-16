#pragma once
#include <vector>
#include <map>

class MenuObject;

class Menu
{
public:
	Menu();
	~Menu();

	std::vector<MenuObject*> mainMenuObj;
	std::vector<MenuObject*> pauseMenuObj;

private:
	std::map<std::string, sf::Texture*> alltex;
	void loadMenus();

};

