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
	void setIsPlayer(bool p) { isPlayer = p; };
	void setTriggerAction(TRIGGER_ACTION_TYPE type) { triggerType = type; };

	void setPosition(float x, float y) { xPos = x; yPos = y; };
	void setScale(float x, float y) { xScale = x; yScale = y; };
	void setRotation(float r) { rotation = r; };

	void setSpeed(float s) { speed = s; };
	void setMovementBehaviour(MOVEMENT_TYPES type) { movementType = type; };
	void setMovementConrolls(int up, int down, int left, int right) { 
		controlls[0] = up;
		controlls[1] = down;
		controlls[2] = left;
		controlls[3] = right;
	};

	void setAttack(int attackNo, ATTACK_TYPES atype, ATTACK_CONDITION_TYPES condType, float xOffset, 
		float yOffset, float xSize, float ySize, float timer, float xOffsetCollision, float yOffsetCollision, 
		float xSizeCollision, float ySizeCollision);

	void setAttackType(int attackNo, ATTACK_TYPES type) { attackType[attackNo] = type; };
	void setAttackCondition(int attackNo, ATTACK_CONDITION_TYPES type) { attackCondition[attackNo] = type; };
	void setAttackSize(int attackNo, float xOffset, float yOffset, float xSize, float ySize){
		attackSize[attackNo][0] = xOffset;
		attackSize[attackNo][1] = yOffset;
		attackSize[attackNo][2] = xSize;
		attackSize[attackNo][3] = ySize;
	};
	void setAttackCollisionBox(int attackNo, float xOffset, float yOffset, float xSize, float ySize) {
		attackCollisionBox[attackNo][0] = xOffset;
		attackCollisionBox[attackNo][1] = yOffset;
		attackCollisionBox[attackNo][2] = xSize;
		attackCollisionBox[attackNo][3] = ySize;
	};
	void setAttackTaget(int attackNo, std::string tag) { attackTarget[attackNo] = tag; };
	void setAttackDirection(int attackNo, float xDir, float yDir) { attackDirX[attackNo] = xDir;	attackDirY[attackNo] = yDir; };
	void setProjectileNumber(int attackNo, int projNo, float angle) { projectileNo[attackNo] = projNo; attacksAngle[attackNo] = angle; };
	void setAttackTexture(int attackNo, std::string filePath) { attackTex[attackNo] = filePath; };
	void setAttackProximity(int attackNo, std::string tag, float distance) { proxTag[attackNo] = tag; proxDistance[attackNo] = distance; };
	void setAttackTimer(int attackNo, float timer) { attackTimer[attackNo] = timer; };
	void setAttackKey(int attackNo, int key) { controlls[3 + attackNo] = key; };

	void setTexture(std::string filePath, bool isAnimated);
	void setAnimation(ANIMATION_TYPES type, int xOffset, int yOffset, int width, int height, int frames) {
		animations[type][0] = xOffset;
		animations[type][1] = yOffset;
		animations[type][2] = width;
		animations[type][3] = height;
		animations[type][4] = frames;
	};

	void writeObject();
	void finishLevel();

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
	bool animated = false;
	int animations[5][5] = { {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0}, {0,0,0,0,0} };

	float speed = 0;
	MOVEMENT_TYPES movementType = MOVEMENT_TYPES::STATIONARY;
	std::vector<int> controlls = { 22,18,0,3,4,16 };

	ATTACK_TYPES attackType[2] = { ATTACK_TYPES::NO_ATTACK, ATTACK_TYPES::NO_ATTACK };
	ATTACK_CONDITION_TYPES attackCondition[2] = { ATTACK_CONDITION_TYPES::NO_COND, ATTACK_CONDITION_TYPES::NO_COND };
	int attackSize[2][4] = { {0,0,0,0},{0,0,0,0} };
	int attackCollisionBox[2][4] = { {0,0,0,0},{0,0,0,0} };
	std::string attackTarget[2] = { "","" };
	float attackDirX[2] = { 0,0 }, attackDirY[2] = { 0,0 };
	int projectileNo[2] = { 0,0 };
	float attacksAngle[2] = { 0,0 };
	std::string attackTex[2] = { "","" };
	std::string proxTag[2] = { "","" };
	float proxDistance[2] = { 0,0 };
	float attackTimer[2] = { 0,0 };

	int objInLvl = 0;
	int levelsPresent = 1;
	std::vector<std::string> allTextures;
};
