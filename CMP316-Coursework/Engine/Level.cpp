#include "pch.h"
#include "Level.h"
#include <fstream>
#include "ENUM_TYPES.h"
#include "MovementComponent.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::loadLevel(int lvlNo)
{
	std::string lvl = "../LoadingFiles/level" + std::to_string(lvlNo);
	std::cout << "Opening from " << lvl << std::endl;
	std::ifstream input;
	input.open(lvl);

	if (!input.is_open())
	{
		std::cout << "err" << std::endl;
		return;
	}
	
	//getting number of objects to initialize
	std::string str;
	input >> str;
	int noObj = std::stoi(str);
	std::cout << "Objects loaded in level " << lvlNo << ": " << noObj << std::endl;

	//getting how many textures need to be loaded
	std::getline(input, str, ':');
	std::getline(input, str, ':');
	int noTxt = std::stoi(str);

	sf::Texture* t;
	for (int i = 0; i < noTxt; i++)
	{
		std::getline(input, str, ';');
		t = new sf::Texture;
		t->loadFromFile(str);
		textureMap.emplace(std::pair<std::string, sf::Texture*>(str, t));
	}

	//for (int i = 0; i < 1; ++i)
	//{
	//	//tag
	//	std::string tag;
	//	std::getline(input, tag, ':');
	//	std::getline(input, tag, ';');
	//	objList.emplace(tag, new GameObject);
	//	objList.at(tag)->setTag(tag);
	//}

	while (std::getline(input, str))
	{
		if (str.find("tag:", 0) != std::string::npos)
		{
			std::cout<<str.substr(4, str.size() - 5);
			objList.emplace(str, new GameObject);
			objList.at(str)->setTag(str);
		}
	}

	//objList.push_back(GameObject());

		////tag
		//std::getline(input, str, ':');
		//std::getline(input, str, ';');
		//objList[i].setTag(str);
		//std::cout << str << std::endl;

		////is player
		//std::getline(input, str, ':');
		//std::getline(input, str, ';');
		////objList[i].setTag(str);
		//std::cout << str << std::endl;

		////trigger type
		//std::getline(input, str, ':');
		//std::getline(input, str, ';');
		////objList[i].setTag(str);
		//std::cout << str << std::endl;

		////transforms
		//std::getline(input, str, ':');
		//std::cout << str;
		////position
		//std::getline(input, str, ';');
		//std::cout << str;
		//objList[i].setPosition(std::stof(str), std::stof(str));
		//std::getline(input, str, ';');
		//std::cout << str;
		//objList[i].setPosition(objList[i].getPosition().x, std::stof(str));
		////scale
		//std::getline(input, str, ';');
		//std::cout << str;
		//objList[i].setScale(std::stof(str), std::stof(str));
		//std::getline(input, str, ';');
		//std::cout << str;
		//objList[i].setScale(objList[i].getPosition().x, std::stof(str));
		////rotation
		//std::getline(input, str, ';');
		//std::cout << str << std::endl;
		//objList[i].setRotation(std::stof(str));

		////texture
		//std::getline(input, str, ':');
		//std::cout << str;
		//std::getline(input, str, ';');
		//std::cout << str;
		//objList[i].setTexture(textureMap.at(str));
		//objList[i].setSize(sf::Vector2f(textureMap.at(str)->getSize().x, textureMap.at(str)->getSize().y));

		////movement
		//std::getline(input, str, ':');
		//std::cout << str;
		////movement type
		//std::getline(input, str, ';');
		//int mt = stoi(str);
		//std::cout << str;

		////speed 
		//std::getline(input, str, ';');
		//float s;
		//s = stof(str);
		//std::cout << str;

		////controlls
		//std::getline(input, str, ':');
		//std::cout << str;
		//int u, d, l, r;

		//std::getline(input, str, ';');
		//std::cout << str;
		//u = stoi(str);
		//std::getline(input, str, ';');
		//std::cout << str;
		//d = stoi(str);
		//std::getline(input, str, ';');
		//std::cout << str;
		//l = stoi(str);
		//std::getline(input, str, ';');
		//std::cout << str;
		//r = stoi(str);
		//objList[i].addComponent(std::make_shared<MovementComponent>(mt, u, d, l, r, s));

	
	input.close();
}

GameObject Level::getGameObj(int n)
{
	return GameObject();
}

