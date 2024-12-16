#pragma once
#include <vector>
#include <string>
#include "ENUM_TYPES.h"

class Object
{
public:
	Object() {};
	~Object() {};

	void setTag(std::string tag) { objTag = tag; };
	void setObjType(OBJECT_TYPE type) { objType = type; };
	void setHealth(int hp) { health = hp; };
	void setTriggerAction(TRIGGER_ACTION_TYPE type) { triggerType = type; };

	void setPosition(float x, float y) { xPos = x; yPos = y; };
	void setScale(float x, float y) { xScale = x; yScale = y; };
	void setRotation(float r) { rotation = r; };
	void setHealth(std::string filepath, float xpos, float ypos, float xsc, float ysc, float r)
	{
		if (allTextures.size() == 0)
		{
			allTextures.push_back(filepath);
		}
		else
		{
			bool alreadyExists = false;
			for (int i = 0; i < allTextures.size(); ++i)
			{
				if (allTextures[i] == filepath)
				{
					alreadyExists = true;
					break;
				}
			}
			if (!alreadyExists)
			{
				allTextures.push_back(filepath);
			}
		}
		healthTex = filepath;
		healthPosX = xpos;
		healthPosY = ypos;
		healthScaleX = xsc;
		healthScaleY = ysc;
		healthRot = r;
	};

	void setSpeed(float s) { speed = s; };
	void setMovementBehaviour(MOVEMENT_TYPES type) { movementType = type; };
	void setFollowTarget(std::string tag, float distanceKept) { followTarget = tag; distKept = distanceKept; };
	void addPatrollPoint(float x, float y) { patPoints.push_back(x); patPoints.push_back(y); };
	void setMovementConrolls(int up, int down, int left, int right) {
		controlls[0] = up;
		controlls[1] = down;
		controlls[2] = left;
		controlls[3] = right;
	};

	void setAttackType(int attackNo, ATTACK_TYPES type) { attackType[attackNo] = type; };
	void setAttackCondition(int attackNo, ATTACK_CONDITION_TYPES type) { attackCondition[attackNo] = type; };
	void setAttackCollisionBox(int attackNo, float xOffset, float yOffset, float xSize, float ySize) {
		attackCollisionBox[attackNo][0] = xOffset;
		attackCollisionBox[attackNo][1] = yOffset;
		attackCollisionBox[attackNo][2] = xSize;
		attackCollisionBox[attackNo][3] = ySize;
	};
	void setAttackTaget(int attackNo, std::string tag, float minDist) { attackTarget[attackNo] = tag; targetMinDist[attackNo] = minDist; };
	void setAttackDirection(int attackNo, float xDir, float yDir) { attackDirX[attackNo] = xDir; attackDirY[attackNo] = yDir; };
	void setAttackDirection(int attackNo, ATTACK_DIRECTION_CONTROLL directionControl) { attDirControll[attackNo] = directionControl; };
	void setProjectileNumber(int attackNo, int projNo, float angle) { projectileNo[attackNo] = projNo; attacksAngle[attackNo] = angle; };
	void setAttackTexture(int attackNo, std::string filePath) { 
		attackTex[attackNo] = filePath; 
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
	};
	void setAttackProximity(int attackNo, std::string tag, float distance) { proxTag[attackNo] = tag; proxDistance[attackNo] = distance; };
	void setAttackMeleTimer(int attackNo, float timer) { meleTimer[attackNo] = timer; };
	void setAttackKey(int attackNo, int key) { controlls[4 + attackNo] = key; };
	void setAttackSpeed(int attackNo, float attackSpeed) { aSpeed[attackNo] = attackSpeed; };
	void setAttackScale(int attackNo, float xSc, float ySc) { aScaleX[attackNo] = xSc; aScaleY[attackNo] = ySc; };
	void setAttackOffset(int attackNo, float x, float y) { aOffsetX[attackNo] = x; aOffsetY[attackNo] = y; };
	void setAttackRotation(int attackNo, float r) { aRot[attackNo] = r; };
	void setAttackCoolDown(int attackNo, float  coolDown) { aCoolDown[attackNo] = coolDown; };
	void setAttackDamage(int attackNo, int dmg) { aDmg[attackNo] = dmg; };

	void setTexture(std::string filePath, bool isAnimated);
	//void setOrigin();
	void setAnimation(ANIMATION_TYPES type, int xOffset, int yOffset, int width, int height, int frames, float speed, bool loop) {
		animations[type - 1][0] = xOffset;
		animations[type - 1][1] = yOffset;
		animations[type - 1][2] = width;
		animations[type - 1][3] = height;
		animations[type - 1][4] = frames;
		aniSpeed[type - 1] = speed;
		aniLoop[type - 1] = loop;
	};

	void writeObject();
	void finishLevel();
	void finished();

private:
	void resetObject();

	std::string objTag = "";
	OBJECT_TYPE objType = OBJECT_TYPE::BACKGROUND;

	bool isPlayer = false;
	TRIGGER_ACTION_TYPE triggerType = TRIGGER_ACTION_TYPE::NO_ACTION;

	float xPos = 0, yPos = 0;
	float xScale = 1, yScale = 1;
	float rotation = 0;

	std::string texPath = { "" };
	std::string healthTex = { "" };
	float healthPosX = 0;
	float healthPosY = 0;
	float healthScaleX = 0;
	float healthScaleY = 0;
	float healthRot = 0;
	bool animated = false;
	int animations[9][5] = { 0 };//{ {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };
	float aniSpeed[9] = { 200 };
	bool aniLoop[9] = { true };

	int health = 5;
	float speed = 0;
	MOVEMENT_TYPES movementType = MOVEMENT_TYPES::STATIONARY;
	std::vector<int> controlls = { 22,18,0,3,4,16 };
	std::string followTarget = "";
	float distKept = 0;
	std::vector<float> patPoints;

	ATTACK_TYPES attackType[2] = { ATTACK_TYPES::NO_ATTACK, ATTACK_TYPES::NO_ATTACK };
	ATTACK_CONDITION_TYPES attackCondition[2] = { ATTACK_CONDITION_TYPES::NO_COND, ATTACK_CONDITION_TYPES::NO_COND };
	int aDmg[2] = { 1 };
	float aScaleX[2] = { 1 };
	float aScaleY[2] = { 1 };
	float attackCollisionBox[2][4] = { {0,0,0,0},{0,0,0,0} };
	std::string attackTarget[2] = { "","" };
	float attackDirX[2] = { 0,0 }, attackDirY[2] = { 0,0 };
	ATTACK_DIRECTION_CONTROLL attDirControll[2] = { ATTACK_DIRECTION_CONTROLL::NO_CONTROL };
	int projectileNo[2] = { 0,0 };
	float attacksAngle[2] = { 0,0 };
	std::string attackTex[2] = { "","" };
	std::string proxTag[2] = { "","" };
	float proxDistance[2] = { 0,0 };
	float meleTimer[2] = { 0,0 };
	float aSpeed[2] = { 200 };
	float aOffsetX[2] = { 0 };
	float aOffsetY[2] = { 0 };
	float aRot[2] = { 0 };
	float aCoolDown[2] = { 0 };
	float targetMinDist[2] = { 0 };

	int objInLvl = 0;
	int levelsPresent = 0;
	std::vector<std::string> allTextures;
};
