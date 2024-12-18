#include "pch.h"
#include "Level.h"
#include <fstream>
#include "ENUM_TYPES.h"
#include "PlayerMovementComponent.h"
#include "FollowMovementComponent.h"
#include "PatrolMovementComponent.h"
#include "AnimationComponent.h"
#include "AttackComponent.h"

Level::Level()
{
	//sets up the poo of attack objects
	//there is a maximum of 500 attacks that can be alive at once
	//theoreticaly this should not be reached, 
	//but if it does happen the only effect it will have on the game is that it will look like objects are lagging a bit
	//since they are waiting for an attack to be freed up
	for (int i = 0; i < 500; i++)
	{
		attacks.emplace(i, new AttackObj);
	}
	loadLevel(0);
}

Level::~Level()
{
}

//parse through the txt file and set up the objects adding components as necessary
void Level::loadLevel(int lvlNo)
{
	nextObjList.clear();
	nextTextureMap.clear();
	nextCollidingObj.clear();

	if (lvlNo != 0)
	{
		allObj = playerObjList;
		nextTextureMap = playerTextureMap;
		for (auto const& plOb : playerObjList)
		{
			nextCollidingObj.push_back(plOb.second);
		}
	}

	std::string lvl = "LoadingFiles/level" + std::to_string(lvlNo);
	std::cout << "Opening from " << lvl << std::endl;
	std::ifstream input;
	input.open(lvl);

	if (!input.is_open())
	{
		std::cout << "err oppening " << lvl << std::endl;
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

		//Object type
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		OBJECT_TYPE objType = static_cast<OBJECT_TYPE>(stoi(str));
		switch (objType)
		{
		case ACTOR:
		{
			it.second->setCharacter(true);
			if (lvlNo == 0)
			{
				it.second->setPlayer(true);
			}
			nextCollidingObj.push_back(it.second);
			break;
		}
		case BACKGROUND:
			break;
		case TERRAIN:
		{
			it.second->setBarrier(true);
			nextCollidingObj.push_back(it.second);
			break;
		}
		case NONE:
			break;
		default:
			break;
		}

		//health
		std::getline(input, str, ';');
		it.second->setHealth(stoi(str));

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

		//health visuals
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		std::string hpTex = str;
		float hppx, hppy, hpsx, hpsy, hpr;
		std::getline(input, str, ';');
		hppx = stof(str);
		std::getline(input, str, ';');
		hppy = stof(str);
		std::getline(input, str, ';');
		hpsx = stof(str);
		std::getline(input, str, ';');
		hpsy = stof(str);
		std::getline(input, str, ';');
		hpr = stof(str);

		it.second->setHPVisuals(nextTextureMap.at(hpTex), hppx, hppy, hpsx, hpsy, hpr);

		//texture
		std::getline(input, str, ':');
		std::getline(input, str, ';');
		it.second->setTexture(nextTextureMap.at(str));
		it.second->setSize(sf::Vector2f(nextTextureMap.at(str)->getSize().x, nextTextureMap.at(str)->getSize().y));
		it.second->setCollisionBox(0, 0, it.second->getSize().x* it.second->getScale().x, it.second->getSize().y* it.second->getScale().y);
		//it.second->setOrigin(sf::Vector2f(nextTextureMap.at(str)->getSize().x / 2, nextTextureMap.at(str)->getSize().y / 2));
		//animated
		std::getline(input, str, ';');
		bool a = stoi(str);

		//animations
		std::getline(input, str, ':');
		int ani[5][5] = { {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };
		float aSpeed[5];
		bool aLoop[5];
		for (int i = 0; i < 5; ++i)
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
		int cA[2];
		std::getline(input, str, ';');
		cA[0] = stoi(str);
		std::getline(input, str, ';');
		cA[1] = stoi(str);

		int at[2], ac[2], pn[2], adirCon[2], aDmg[2];
		float adx[2], ady[2], proxdis[2], aspee[2], aScalX[2], aScalY[2], aAng[2], amt[2], aOffX[2], aOffY[2], aRot[2], acd[2], atarMinDis[2];
		std::string atar[2], atex[2], prox[2];
		float acolBox[2][4];

		GameObject* atarget[2] = { nullptr };
		GameObject* proxiObj[2] = { nullptr };

		//attack 
		std::getline(input, str, ':');
		for (int i = 0; i < 2; i++)
		{
			std::getline(input, str, ':');
			//type
			std::getline(input, str, ';');
			at[i] = stoi(str);
			//damage
			std::getline(input, str, ';');
			aDmg[i] = stoi(str);
			//condition
			std::getline(input, str, ';');
			ac[i] = stoi(str);
			//scale
			std::getline(input, str, ';');
			aScalX[i] = stof(str);
			std::getline(input, str, ';');
			aScalY[i] = stof(str);
			//collisions
			for (int j = 0; j < 4; j++)
			{
				std::getline(input, str, ';');
				acolBox[i][j] = stof(str);
			}
			//target
			std::getline(input, str, ';');
			atar[i] = str;
			if (str != "")
			{
				atarget[i] = allObj.at(atar[i]);
			}			
			//direction
			std::getline(input, str, ';');
			adx[i] = stof(str);
			std::getline(input, str, ';');
			ady[i] = stof(str);
			//direction controll
			std::getline(input, str, ';');
			adirCon[i] = stoi(str);
			//projectile no
			std::getline(input, str, ';');
			pn[i] = stoi(str);
			//attacks angle
			std::getline(input, str, ';');
			aAng[i] = stof(str);
			//attack texture
			std::getline(input, str, ';');
			atex[i] = str;
			if (str == "")
			{
				atex[i] = "res/animationTest.png";
			}
			//proximity target tag
			std::getline(input, str, ';');
			prox[i] = str;
			if (str != "")
			{
				proxiObj[i] = allObj.at(str);
			}
			//proximity target distance
			std::getline(input, str, ';');
			proxdis[i] = stof(str);
			//mele timer
			std::getline(input, str, ';');
			amt[i] = stof(str);
			std::getline(input, str, ';');
			//speed
			aspee[i] = stof(str);
			//position offset
			std::getline(input, str, ';');
			aOffX[i] = stof(str);
			std::getline(input, str, ';');
			aOffY[i] = stof(str);
			//roatation
			std::getline(input, str, ';');
			aRot[i] = stof(str);
			//cool down
			std::getline(input, str, ';');
			acd[i] = stof(str);
			//min target distance
			std::getline(input, str, ';');
			atarMinDis[i] = stof(str);

			if (static_cast<ATTACK_TYPES>(at[i]) != ATTACK_TYPES::NO_ATTACK)
			{
				it.second->addComponent(std::make_shared<AttackComponent>(&attacks, nextTextureMap.at(atex[i]), adx[i],
					ady[i], aspee[i], aScalX[i], aScalY[i], cA[i], static_cast<ATTACK_TYPES>(at[i]),
					static_cast<ATTACK_CONDITION_TYPES>(ac[i]), acolBox[i], atarget[i],
					static_cast<ATTACK_DIRECTION_CONTROLL>(adirCon[i]), pn[i], aAng[i], proxdis[i], amt[i],
					aOffX[i], aOffY[i], aRot[i], acd[i], atarMinDis[i], proxiObj[i], aDmg[i]));
			}
		}


		//add animation component after movement so i can check object velocity in animation to flip it if necessary 
		if (a)
		{
			it.second->addComponent(std::make_shared<AnimationComponent>(ani, aSpeed, aLoop));
			it.second->setSize(sf::Vector2f(ani[0][2], ani[0][3]));
			it.second->setCollisionBox(0, 0, it.second->getSize().x*it.second->getScale().x, it.second->getSize().y * it.second->getScale().y);
			//it.second->setOrigin(ani[0][3] / 2, ani[0][4] / 2);
			
		}
	}

	input.close();

	//player characters are stored in level 0, they get passed from level to level so that parameters dont get lost 
	//or values dont het reset, like hp
	if (lvlNo == 0)
	{
		playerObjList = nextObjList;
		playerTextureMap = nextTextureMap;
	}
}

//swap current level to the loaded level
void Level::switchLevel()
{
	//std::cout << "Switched level";
	objList = nextObjList;
	textureMap = nextTextureMap;
	collidingObj = nextCollidingObj;
}
