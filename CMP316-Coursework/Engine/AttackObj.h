#pragma once
#include "GameObject.h"
#include "ENUM_TYPES.h"

class AttackObj : public GameObject
{
public:
	AttackObj() { alive = false; };

	void initialize(sf::Vector2f p, sf::Vector2f s, sf::Vector2f dir, float r, float sp, float maxT, bool mele);
	void handleInput(float dt) override;
	void update(float dt) override;

private:
	sf::Vector2f position = sf::Vector2f(0, 0);
	sf::Vector2f scale = sf::Vector2f(0, 0);
	float rotation = 0;
	float speed;
	sf::Vector2f direction = sf::Vector2f(0, 0);
	float maxTimer = 0;
	float isMele = false;
	float timer = 0;
};

