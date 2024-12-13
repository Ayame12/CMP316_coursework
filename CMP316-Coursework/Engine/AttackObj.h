#pragma once
#include "GameObject.h"

class AttackObj : public GameObject
{
public:
	AttackObj();

private:
	bool isMele;
	GameObject* parent;
	float xOffset = 0, yOffset = 0;
	float speed;


};

