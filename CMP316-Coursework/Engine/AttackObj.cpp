#include "pch.h"
#include "AttackObj.h"

void AttackObj::initialize(sf::Vector2f p, sf::Vector2f s, sf::Vector2f dir, float r, float sp, float mt, bool mele, bool isPl)
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
	isPlayer = isPl;
}

void AttackObj::handleInput(float dt)
{
}

void AttackObj::update(float dt)
{
	move(direction * speed * dt);
	//setPosition(sf::Vector2f(getPosition().x + direction.x * speed * dt, getPosition().y + direction.y * speed * dt));
	//sf::Vector2f testvec = getPosition();
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
	/*if (getPosition().x <-20 || getPosition().y <-20 || getPosition().x >window->getSize().x + 20 || getPosition().y >window->getSize().y + 20)
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
