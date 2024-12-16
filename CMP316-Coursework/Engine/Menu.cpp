#include "pch.h"
#include "Menu.h"
#include "MenuObject.h"
#include <fstream>>

Menu::Menu()
{
	loadMenus();
}

Menu::~Menu()
{
}

void Menu::loadMenus()
{
	std::ifstream input;
	input.open("Menus");
	std::string str;

	std::getline(input, str, ':');
	int texNo = stoi(str);
	sf::Texture* t;
	for (int i = 0; i < texNo; i++)
	{
		std::getline(input, str, ':');
		t = new sf::Texture;
		t->loadFromFile(str);
		alltex.emplace(std::pair<std::string, sf::Texture*>(str, t));
	}

	std::vector< MenuObject*> vec;
	
	vec.push_back(new MenuObject);
	
	int i = -1;

	for (int k = 0; k < 2; k++)
	{
		++i;

		//menu type
		std::getline(input, str, ';');
		int menuType = stoi(str);

		//bg tex
		std::getline(input, str, ';');
		vec[i]->setTexture(alltex.at(str));
		vec[i]->setSize(sf::Vector2f(alltex.at(str)->getSize().x, alltex.at(str)->getSize().y));

		//text
		std::getline(input, str, ';');
		vec[i]->text.setString(str);
		std::getline(input, str, ';');
		float xp = stof(str);
		std::getline(input, str, ';');
		float yp = stof(str);
		vec[i]->text.setPosition(xp, yp);

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
		vec[i]->text.setScale(xp, yp);

		std::getline(input, str, ':');
		int bNo = stoi(str);
		for (int j = 0; j <= bNo; j++)
		{
			++i;
			vec.push_back(new MenuObject);

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

	
	/*
	for (int j = 0; j < buttonXPos->size(); j++)
	{
		out << buttonXPos[i][j] << ";";
		out << buttonYPos[i][j] << ";";
		out << buttonText[i][j] << ";";
		out << buttonNormTxt[i][j] << ";";
		out << buttonHighTxt[i][j] << ";";
		out << levelTarget[i][j] << ";";
		out << buttonXScale[i][j] << ";";
		out << buttonYScale[i][j] << ";";
	}*/
}
