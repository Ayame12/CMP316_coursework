#pragma once
#include "Component.h"
#include "ENUM_TYPES.h"

class AttackObj;

class AttackComponent : public Component
{
public:
	AttackComponent(float xo, float yo, float sx, float sy, float r, ATTACK_TYPES at,
		float s, float xDir,float yDir, ATTACK_CONDITION_TYPES ac, ATTACK_DIRECTION_CONTROLL adc, GameObject* t,
		float cd, float tDist, int c, std::map<int, AttackObj*>* map, sf::Texture* tex, float mt)
	{
		xOffset = xo; yOffset = yo; scale = sf::Vector2f(sx, sy); rotation = r; 
		type = at; speed = s; cond = ac; dirCon = adc; target = t; coolDown = cd;
		targetMinDist = tDist; control = c; allattacks = map; direction = sf::Vector2f(xDir, yDir);
		texture = tex; meleMaxTimer = mt;
	};

	void handleInput(GameObject* gameObject, float dt) override;
	void update(GameObject* gameObject, float dt) override;

private:
	int index = 0;
	bool found = false;
	bool canSpawn = true;
	bool isMele = false;
	bool fired = false;
	float xOffset = 0, yOffset = 0;
	sf::Vector2f scale = sf::Vector2f(1, 1);
	sf::Vector2f position = sf::Vector2f(0, 0);
	float rotation = 0;
	float coolDown = 0.5;
	float timePassed = 0;
	float targetMinDist = 0;
	int control = 100;
	float meleMaxTimer = 100;

	std::map<int, AttackObj*>* allattacks = nullptr;
	sf::Texture* texture = nullptr;

	ATTACK_TYPES type = ATTACK_TYPES::NO_ATTACK;
	float speed = 0;
	ATTACK_CONDITION_TYPES cond = ATTACK_CONDITION_TYPES::NO_COND;
	ATTACK_DIRECTION_CONTROLL dirCon = ATTACK_DIRECTION_CONTROLL::MOUSE;
	GameObject* target = nullptr;

	sf::Vector2f direction = sf::Vector2f(0, 0);
};

