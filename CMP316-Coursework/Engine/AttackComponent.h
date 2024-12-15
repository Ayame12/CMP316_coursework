#pragma once
#include "Component.h"
#include "ENUM_TYPES.h"

class AttackObj;

class AttackComponent : public Component
{
public:
	AttackComponent(std::map<int, AttackObj*>* allAtc, sf::Texture* tex, float dirX, float dirY, float spee, float scaleX,
		float scaleY, int cont, ATTACK_TYPES at, ATTACK_CONDITION_TYPES condition, float colBOx[4], GameObject* tar,
		ATTACK_DIRECTION_CONTROLL directionContro, int projNo, float angle, float proxDist, float meleTim, float xOff,
		float yOff, float rot, float cd, float targetDistance, GameObject* prox, int dmg)
	{
		allattacks = allAtc;
		texture = tex;

		direction = sf::Vector2f(dirX, dirY);

		speed = spee;
		scale = sf::Vector2f(scaleX, scaleY);

		control = cont;
		type = at;
		cond = condition;
		attackCollisionBox[0] = colBOx[0];
		attackCollisionBox[1] = colBOx[1];
		attackCollisionBox[2] = colBOx[2];
		attackCollisionBox[3] = colBOx[3];
		target = tar;
		dirCon = directionContro;
		projectileNo = projNo;
		attacksAngle = angle;
		proximityDistance = proxDist;
		meleMaxTimer = meleTim;
		xOffset = xOff;
		yOffset = yOff;
		initRotation = rot;
		coolDown = cd;
		targetMinDist = targetDistance;
		proxiObj = prox;
		damage = dmg;
	};

	void handleInput(GameObject* gameObject, float dt) override;
	void update(GameObject* gameObject, float dt) override;

private:
	int index = 0;
	bool found = false;
	bool canSpawn = true;
	bool isMele = false;
	bool fired = false;
	int damage = 1;

	std::map<int, AttackObj*>* allattacks = nullptr;
	sf::Texture* texture = nullptr;
	float timePassed = 0;
	sf::Vector2f direction = sf::Vector2f(0, 0);
	sf::Vector2f position = sf::Vector2f(0, 0);
	float speed = 2000;
	sf::Vector2f scale = sf::Vector2f(0, 0);
	float initRotation;
	int control = 2;
	ATTACK_TYPES type = ATTACK_TYPES::NO_ATTACK;
	ATTACK_CONDITION_TYPES cond = ATTACK_CONDITION_TYPES::NO_COND;
	float attackCollisionBox[4] = { 0,0,0,0 };
	GameObject* target = nullptr;
	GameObject* proxiObj = nullptr;
	ATTACK_DIRECTION_CONTROLL dirCon = ATTACK_DIRECTION_CONTROLL::NO_CONTROL;
	int projectileNo = 0;
	float attacksAngle = 0;
	std::string attackTex = "";
	float proximityDistance = 0;
	float meleMaxTimer = 0;
	float xOffset = 0;
	float yOffset = 0;
	float rotation = 0;
	float coolDown = 0;
	float targetMinDist = 0;
};

