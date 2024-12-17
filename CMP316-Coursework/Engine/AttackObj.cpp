#include "pch.h"
#include "AttackObj.h"

void AttackObj::initialize(sf::Vector2f p, sf::Vector2f s, sf::Vector2f dir, float r, float sp, float mt, bool mele, bool isPl, int dmg)
{
	setOrigin(getSize().x / 2, getSize().y / 2);
	setPosition(p);
	setScale(s); 
	setRotation(r);
	speed = sp;
	direction = dir;
	setAlive(true);
	maxTimer = mt; 
	isMele = mele;
	timer = 0;
	isPlayer = isPl;
	damage = dmg;
}

void AttackObj::handleInput(float dt)
{
}

void AttackObj::update(float dt)
{
	move(direction * speed * dt);

	sf::Vector2f cen = window->getView().getCenter();
	sf::Vector2f siz = window->getView().getSize();
	if (getPosition().x < cen.x - siz.x / 2 - 100 ||
		getPosition().y < cen.y - siz.y / 2 - 100 ||
		getPosition().x > cen.x + siz.x / 2 + 100 ||
		getPosition().x > cen.x + siz.x / 2 + 100)
	{
		alive = false;
	}
	if (isMele)
	{
		timer += dt;
		if (timer > maxTimer)
		{
			alive = false;
		}
	}
}
