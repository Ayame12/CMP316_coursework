#include "pch.h"
#include "ObjectMaker.h"
#include <fstream>

//adds all the textures for the level in one vector so that they are only loaded once
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

//writes an object to the level file
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
		//appens the file in 'edit' mode if there is already another object written
		out.open(currentlvl, std::ios_base::app);
	}
	objInLvl++;
	
	out << "tag:" << objTag << ";" << std::endl;
	out << "objectType:" << objType << ";" << health << ";" << std::endl;
	out << "triggerType:" << triggerType << ";" << std::endl;

	out << "transforms:" << xPos << ";" << yPos << ";" << xScale << ";" << yScale << ";" << rotation << ";" << std::endl;

	out << "health:" << healthTex << ";" << healthPosX << ";" << healthPosY << ";" << healthScaleX << ";" << healthScaleY << ";" << healthRot << ";" << std::endl;
	
	out << "visual:" << texPath << ";";
	out << animated << ";" << std::endl;

	out << "animations:";
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			out << animations[i][j] << ";";
		}
		out << aniSpeed[i] << ";" << int(aniLoop) << ";";
	}
	out << std::endl;

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
	out << "attacks:";
	for (int i = 0; i < 2; i++)
	{
		out << i << ":";
		out << attackType[i] << ";";
		out << aDmg[i] << ";";
		out << attackCondition[i] << ";";
		out << aScaleX[i] << ";";
		out << aScaleY[i] << ";";
		for (int j = 0; j < 4; j++) {
			out << attackCollisionBox[i][j] << ";";
		}
		out << attackTarget[i] << ";";
		out << attackDirX[i] << ";";
		out << attackDirY[i] << ";";
		out << attDirControll[i] << ";";
		out << projectileNo[i] << ";";
		out << attacksAngle[i] << ";";
		out << attackTex[i] << ";";
		out << proxTag[i] << ";";
		out << proxDistance[i] << ";";
		out << meleTimer[i] << ";";
		out << aSpeed[i] << ";";
		out << aOffsetX[i] << ";";
		out << aOffsetY[i] << ";";
		out << aRot[i] << ";";
		out << aCoolDown[i] << ";";
		out << targetMinDist[i] << ";";
	}

	out.close();
	resetObject();
}

//rewrites the whole file placing inportant information at the top
void Object::finishLevel()
{
	std::string currentlvl = "../LoadingFiles/level" + std::to_string(levelsPresent);
	std::ifstream input;
	input.open(currentlvl);

	//copies file before rewriting
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
	
	//writes all the textures at the top, for loading in a map and the number of objects inside the level
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

void Object::finished()
{
	std::string str = "../LoadingFiles/fin";
	std::ofstream out;
	out.open(str);
	out << levelsPresent - 1;
	out.close();
}

//reset parameters
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
	health = 5;

	texPath = { "" };
	animated = false;
	for (int i = 0; i < 5; ++i) {
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

	for (int i = 0; i < 2; i++) {
		attackType[i] = ATTACK_TYPES::NO_ATTACK;
		attackCondition[i] = ATTACK_CONDITION_TYPES::NO_COND;
		aScaleX[i] = 1;
		aScaleY[i] = 1;
		aDmg[i] = 1;

		for (int j = 0; j < 4; j++) {
			attackCollisionBox[i][j] = 0;
		}

		attackTarget[i] = "";
		attackDirX[i] = 0;
		attackDirY[i] = 0;
		attDirControll[i] = ATTACK_DIRECTION_CONTROLL::NO_CONTROL;
		projectileNo[i] = 0;
		attacksAngle[i] = 0;
		attackTex[i] = "";
		proxTag[i] = "";
		proxDistance[i] = 0;
		meleTimer[i] = 0;
		aSpeed[i] = 200;
		aOffsetX[i] = 0;
		aOffsetY[i] = 0;
		aRot[i] = 0;
		aCoolDown[i] = 0;
		targetMinDist[i] = 0;
	}
}
