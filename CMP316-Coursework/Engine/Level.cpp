#include "pch.h"
#include "Level.h"
#include <fstream>
#include "ENUM_TYPES.h"
#include "PlayerMovementComponent.h"
#include "FollowMovementComponent.h"
#include "PatrolMovementComponent.h"
#include "AnimationComponent.h"

Level::Level()
{
	loadLevel(0);
}

Level::~Level()
{
}

void Level::loadLevel(int lvlNo)
{
	nextObjList.clear();
	nextTextureMap.clear();
	if (lvlNo != 0)
	{
		allObj = playerObjList;
	}

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
		nextTextureMap.emplace(std::pair<std::string, sf::Texture*>(str, t));
	}

	while (std::getline(input, str))
	{
		if (str.find("tag:", 0) != std::string::npos)
		{
			str = str.substr(4, str.size() - 5);
			nextObjList.emplace(str, new GameObject);
			allObj.emplace(str, nextObjList.at(str));
			nextObjList.at(str)->setTag(str);
		}
	}

	input.clear();
	input.seekg(0);
	input >> str;
	input >> str;

	for (auto const& it : nextObjList)
	{
		//skip tag
		input >> str;

		//trigger action
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		TRIGGER_ACTION_TYPE tra = static_cast<TRIGGER_ACTION_TYPE>(stoi(str));
		switch (tra)
		{
		case LOAD_NEXT_LVL:
			break;
		case ENTER_NEXT_LVL:
			break;
		case NO_ACTION:
			break;
		default:
			break;
		}

		//transforms
		std::getline(input, str, ':');
		//position
		float fx, fy;
		std::getline(input, str, ';');
		fx = stof(str);
		std::getline(input, str, ';');
		fy = stof(str);
		it.second->setPosition(fx, fy);
		//scale
		std::getline(input, str, ';');
		fx = stof(str);
		std::getline(input, str, ';');
		fy = stof(str);
		it.second->setScale(fx, fy);
		//rotation
		std::getline(input, str, ';');
		fx = stof(str);
		it.second->setRotation(fx);

		//texture
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		it.second->setTexture(nextTextureMap.at(str));
		it.second->setSize(sf::Vector2f(nextTextureMap.at(str)->getSize().x, nextTextureMap.at(str)->getSize().y));
		it.second->setOrigin(sf::Vector2f(nextTextureMap.at(str)->getSize().x / 2, nextTextureMap.at(str)->getSize().y / 2));
		//animated
		std::getline(input, str, ';');
		bool a = stoi(str);

		//animations
		std::getline(input, str, ':');
		int ani[9][5] = { {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };
		float aSpeed[9];
		bool aLoop[9];
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				std::getline(input, str, ';');
				ani[i][j] = stoi(str);
			}
			std::getline(input, str, ';');
			aSpeed[i] = stof(str);
			std::getline(input, str, ';');
			aLoop[i] = stoi(str);
		}

		//movement
		std::getline(input, str, ':');
		//movement type
		std::getline(input, str, ';');
		MOVEMENT_TYPES mt = static_cast<MOVEMENT_TYPES>(stoi(str));
		//speed
		int s;
		std::getline(input, str, ';');
		s = stof(str);

		//follow target
		std::string ftg;
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		ftg = str;

		//distance kept
		float disk;
		std::getline(input, str, ';');
		disk = stof(str);

		//patrol points
		std::vector<sf::Vector2f> patPoints;
		std::getline(input, str, ':');
		std::getline(input, str, ':');
		int e = stoi(str) / 2;
		for (int i = 0; i < e; ++i)
		{
			std::getline(input, str, ';');
			fx = stof(str);
			std::getline(input, str, ';');
			fy = stof(str);
			patPoints.push_back(sf::Vector2f(fx, fy));
		}

		//controlls
		std::getline(input, str, ':');
		int u, d, l, r;
		std::getline(input, str, ';');
		u = stoi(str);
		std::getline(input, str, ';');
		d = stoi(str);
		std::getline(input, str, ';');
		l = stoi(str);
		std::getline(input, str, ';');
		r = stoi(str);

		switch (mt)
		{
		case STATIONARY:
			break;
		case PATROL:
			it.second->addComponent(std::make_shared<PatrolMovementComponent>(patPoints, s));
			break;
		case FOLLOW:
			it.second->addComponent(std::make_shared<FollowMovementComponent>(allObj.at(ftg), s, disk));
			break;
		case PLAYER_CONTROL:
			it.second->addComponent(std::make_shared<PlayerMovementComponent>(u, d, l, r, s));
			break;
		default:
			break;
		}

		//attacks controlls
		int cA1;
		std::getline(input, str, ';');
		cA1 = stoi(str);
		int cA2;
		std::getline(input, str, ';');
		cA2 = stoi(str);

		//attack Types
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		std::getline(input, str, ':');
		std::getline(input, str, ';');

		//add animation component after movement so i can check object velocity in animation to flip it if necessary 
		if (a)
		{
			it.second->addComponent(std::make_shared<AnimationComponent>(ani, aSpeed, aLoop));
			it.second->setSize(sf::Vector2f(ani[0][3], ani[0][4]));
			it.second->setOrigin(ani[0][3] / 2, ani[0][4] / 2);
		}
	}

	input.close();

	if (lvlNo == 0)
	{
		playerObjList = nextObjList;
		playerTextureMap = nextTextureMap;
	}
}

void Level::switchLevel()
{
	objList = nextObjList;
	textureMap = nextTextureMap;
}
