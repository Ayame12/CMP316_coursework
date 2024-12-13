#include "pch.h"
#include "ObjectMaker.h"
#include <fstream>

void Object::setAttack(int no, ATTACK_TYPES atype, ATTACK_CONDITION_TYPES condType, float xOffset, float yOffset, float xSize, float ySize, float timer, float xOffsetCollision, float yOffsetCollision, float xSizeCollision, float ySizeCollision)
{
	setAttackType(no, atype);
	setAttackCondition(no, condType);
	setAttackSize(no, xOffset, yOffset, xSize, ySize);
	setAttackTimer(no, timer);
	setAttackCollisionBox(no, xOffsetCollision, yOffsetCollision, xSizeCollision, ySizeCollision);
}

void Object::setTexture(std::string filePath, bool isAnimated)
{
	animated = isAnimated;
	texPath = filePath;
	if (allTextures.size() == 0)
	{
		allTextures.push_back(filePath);
	}
	else 
	{
		bool alreadyExists = false;
		for (int i = 0; i < allTextures.size(); ++i)
		{
			if (allTextures[i] == filePath)
			{
				alreadyExists = true;
				break;
			}
		}
		if (!alreadyExists)
		{
			allTextures.push_back(filePath);
		}
	}
	
}

void Object::writeObject()
{
	std::string currentlvl = "../LoadingFiles/level" + std::to_string(levelsPresent);
	std::ofstream out;
	if (objInLvl == 0)
	{
		out.open(currentlvl);
	}
	else
	{
		out.open(currentlvl, std::ios_base::app);
	}
	objInLvl++;
	
	out << "tag:" << objTag << ";" << std::endl;
	//out << "isPlayer:" << isPlayer << ";" << std::endl;
	out << "triggerType:" << triggerType << ";" << std::endl;
	//std::string objTag = "";
	//bool isPlayer = false;

	out << "transforms:" << xPos << ";" << yPos << ";" << xScale << ";" << yScale << ";" << rotation << ";" << std::endl;
	//float xPos = 0, yPos = 0;
	//float xScale = 1, yScale = 1;
	//float rotation = 0;
	
	out << "visual:" << texPath << ";";
	out << animated << ";" << std::endl;

	out << "animations:";
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			out << animations[i][j] << ";";
		}
		out << aniSpeed[i] << ";" << int(aniLoop) << ";";
	}
	out << std::endl;
	//std::string texPath = { "" };
	//bool animated = false;
	//int animations[5][5] = { {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };

	out << "movement:" << movementType << ";" << speed << ";" << std::endl;
	out << "followTarget:" << followTarget << ";" << distKept << ";" << std::endl;
	out << "patrolPoints:" << patPoints.size() << ":";
	for (int i = 0; i < patPoints.size(); ++i)
	{
		out << patPoints[i] << ";";
	}
	out << std::endl;
	out << "controlls:";
	for (int i = 0; i < controlls.size(); i++)
	{
		out << controlls[i] << ";";
	}
	out << std::endl;
	//float xVelocity = 0, yVelocity = 0;
	//MOVEMENT_TYPES movementType = MOVEMENT_TYPES::STATIONARY;
	//std::vector<int> controlls = { 22,18,0,3,4,16 };

	out << "attack1:" << attackType[0] << ";" << std::endl;
	out << "attack2:" << attackType[1] << ";" << std::endl;

	out << "attackDirControll:" << attDirControll[0] << ";" << attDirControll[1] << ";" << std::endl;
		//ATTACK_TYPES attackType[2] = { ATTACK_TYPES::NONE, ATTACK_TYPES::NONE };
		//ATTACK_CONDITION_TYPES attackCondition[2] = { ATTACK_CONDITION_TYPES::NO, ATTACK_CONDITION_TYPES::NO };
		//int attackSize[2][4] = { {0,0,0,0},{0,0,0,0} };
		//int attackCollisionBox[2][4] = { {0,0,0,0},{0,0,0,0} };
		//std::string attackTarget[2] = { "","" };
		//float attackDirX[2] = { 0,0 }, attackDirY[2] = { 0,0 };
		//int projectileNo[2] = { 0,0 };
		//float attacksAngle[2] = { 0,0 };
		//std::string attackTex[2] = { "","" };
		//std::string proxTag[2] = { "","" };
		//float proxDistance[2] = { 0,0 };
		//float attackTimer[2] = { 0,0 };

	out.close();
	resetObject();
}

void Object::finishLevel()
{
	std::string currentlvl = "../LoadingFiles/level" + std::to_string(levelsPresent);
	std::ifstream input;
	input.open(currentlvl);

	std::vector<std::string> linesVec;
	std::string line;
	while (std::getline(input, line))
	{
		linesVec.push_back(line);
	}
	
	input.close();

	std::ofstream out;
	out.open(currentlvl);
	out << objInLvl << std::endl;
	
	out << "allTextures:";
	out << allTextures.size() << ":";
	for (int i = 0; i < allTextures.size(); ++i)
	{
		out << allTextures[i] << ";";
	}
	out << std::endl;
	allTextures.clear();

	for (int i = 0; i < linesVec.size(); ++i)
	{
		out << linesVec[i] << std::endl;
	}
	objInLvl = 0;
	levelsPresent++;
}

void Object::resetObject()
{
	objTag = "";
	isPlayer = false;
	triggerType = TRIGGER_ACTION_TYPE::NO_ACTION;

	objType = OBJECT_TYPE::BACKGROUND;

	xPos = 0;
	yPos = 0;
	xScale = 1;
	yScale = 1;
	rotation = 0;

	texPath = { "" };
	animated = false;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 5; ++j) {
			animations[i][j] = 0;
		}
		aniSpeed[i] = 200;
		aniLoop[i] = true;
	}

	speed = 0;
	movementType = MOVEMENT_TYPES::STATIONARY;
	controlls = { 22, 18, 0, 3, 4, 16 };
	followTarget = "";
	distKept = 0;
	patPoints.clear();

	attackType[0] = ATTACK_TYPES::NO_ATTACK;
	attackType[1] = ATTACK_TYPES::NO_ATTACK;
	attackCondition[0] = ATTACK_CONDITION_TYPES::NO_COND;
	attackCondition[1] = ATTACK_CONDITION_TYPES::NO_COND;

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			attackSize[i][j] = 0;
			attackCollisionBox[i][j] = 0;
		}
		attackTarget[i] = "";
		attackDirX[i] = 0;
		attackDirY[i] = 0;
		projectileNo[i] = 0;
		attacksAngle[i] = 0;
		attackTex[i] = "";
		proxTag[i] = "";
		proxDistance[i] = 0;
		attackTimer[i] = 0;
	}
}
