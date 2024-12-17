#include "pch.h"
#include "Menu.h"
#include <fstream>>

Menu::Menu()
{
	loadMenus();
}

Menu::~Menu()
{
}

//parses through menu file to create the main and pause menus
void Menu::loadMenus()
{
	sf::Font* font;
	font = new sf::Font;
	font->loadFromFile("res/arial.ttf");

	std::ifstream input;
	input.open("../LoadingFiles/Menus");
	std::string str;

	std::getline(input, str, ':');
	int texNo = stoi(str);
	sf::Texture* t;
	for (int i = 0; i < texNo; i++)
	{
		std::getline(input, str, ';');
		t = new sf::Texture;
		t->loadFromFile(str);
		alltex.emplace(std::pair<std::string, sf::Texture*>(str, t));
	}

	std::vector< MenuObject*> vec;
	
	

	for (int k = 0; k < 2; k++)
	{
		int i = 0;

		vec.clear();
		vec.push_back(new MenuObject);

		//menu type
		std::getline(input, str, ';');
		int menuType = stoi(str);

		//bg tex
		std::getline(input, str, ';');
		vec[i]->setTexture(alltex.at(str));
		vec[i]->setSize(sf::Vector2f(alltex.at(str)->getSize().x, alltex.at(str)->getSize().y));
		vec[i]->setOrigin(sf::Vector2f(alltex.at(str)->getSize().x / 2, alltex.at(str)->getSize().y / 2));

		//text
		std::getline(input, str, ';');
		vec[i]->text.setString(str);
		std::getline(input, str, ';');
		float xp = stof(str);
		std::getline(input, str, ';');
		float yp = stof(str);
		vec[i]->text.setPosition(xp, yp);
		//vec[i]->text.setColor(sf::Color::White);
		vec[i]->text.setFont(*font);

		//bg position
		std::getline(input, str, ';');
		xp = stof(str);
		std::getline(input, str, ';');
		yp = stof(str);
		vec[i]->setPosition(xp, yp);

		//bg scale
		std::getline(input, str, ';');
		xp = stof(str);
		std::getline(input, str, ';');
		yp = stof(str);
		vec[i]->setScale(xp, yp);

		//text size
		std::getline(input, str, ';');
		xp = stof(str);
		std::getline(input, str, ';');
		yp = stof(str);
		vec[i]->text.setScale(yp, yp);
		vec[i]->text.setCharacterSize(xp);

		if (menuType == 0)
		{
			menuBg = vec[i];
		}
		else
		{
			pauseBg = vec[i];
		}
		vec.clear();

		std::getline(input, str, ':');
		int bNo = stoi(str);
		for (i = 0; i < bNo; i++)
		{
			if (i == 0)
			{
				vec.push_back(new MenuObject);
				vec[i]->isSelected = true;
			}
			if (i == bNo - 1) 
			{
				vec[i]->nextButton = vec[0];
			}
			else
			{
				vec.push_back(new MenuObject);
				vec[i]->nextButton = vec[i + 1];
			}

			//button pos
			std::getline(input, str, ';');
			xp = stoi(str);
			std::getline(input, str, ';');
			yp = stoi(str);
			vec[i]->setPosition(xp, yp);

			//button text
			std::getline(input, str, ';');
			vec[i]->text.setString(str);

			//normal texture
			std::getline(input, str, ';');
			vec[i]->NormalTex = alltex.at(str);
			vec[i]->setTexture(alltex.at(str));
			vec[i]->setSize(sf::Vector2f(alltex.at(str)->getSize().x, alltex.at(str)->getSize().y));
			vec[i]->setOrigin(sf::Vector2f(alltex.at(str)->getSize().x / 2, alltex.at(str)->getSize().y / 2));

			//highlight texture
			std::getline(input, str, ';');
			vec[i]->HighTex = alltex.at(str);

			//level target
			std::getline(input, str, ';');
			vec[i]->target = stoi(str);

			//button scale
			std::getline(input, str, ';');
			xp = stoi(str);
			std::getline(input, str, ';');
			yp = stoi(str);
			vec[i]->setScale(xp, yp);

			//button text scale
			std::getline(input, str, ';');
			xp = stoi(str);
			std::getline(input, str, ';');
			yp = stoi(str);
			vec[i]->text.setScale(yp, yp);
			vec[i]->text.setCharacterSize(xp);

			//text pos
			std::getline(input, str, ';');
			xp = stof(str);
			std::getline(input, str, ';');
			yp = stof(str);
			vec[i]->text.setPosition(xp, yp);

			vec[i]->text.setFont(*font);
		}

		if (menuType == 0)
		{
			mainMenuObj = vec;
		}
		else
		{
			pauseMenuObj = vec;
		}
	}
}
