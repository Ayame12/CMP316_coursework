#include "pch.h"
#include "AttackObj.h"

void AttackObj::initialize(sf::Vector2f p, sf::Vector2f s, sf::Vector2f dir, float r, float sp, float mt, bool mele)
{
	setPosition(p);
	setScale(s); 
	setRotation(r);
	speed = sp;
	direction = dir;
	setAlive(true);
	maxTimer = mt; 
	isMele = mele;
	timer = 0;
}

void AttackObj::handleInput(float dt)
{
}

void AttackObj::update(float dt)
{
	//move(direction * speed * dt);
	setPosition(sf::Vector2f(getPosition().x + direction.x * speed * dt, getPosition().y + direction.y * speed * dt));
	/*if (getPosition().x * scale.x <-20 || getPosition().y * scale.y <-20 || getPosition().x * scale.x >window->getSize().x + 20 || getPosition().y * scale.y >window->getSize().y + 20)
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
	}*/
	if (getPosition().x <-20 || getPosition().y <-20 || getPosition().x >window->getSize().x + 20 || getPosition().y >window->getSize().y + 20)
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
