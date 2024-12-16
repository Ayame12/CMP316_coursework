#pragma once
#include "Input.h"
#include <vector>
#include <memory>
#include "Component.h"

class GameObject : public sf::RectangleShape
{
public:
	GameObject();
	~GameObject();

	virtual void handleInput(float dt);
	virtual void update(float dt);
	//virtual void render();

	void setAlive(bool s) { alive = s; };
	bool isAlive() { return alive; };

	void setTag(std::string t) { tag = t; };

	void setVelocity(sf::Vector2f v) { velocity = v; };
	sf::Vector2f getVelocity() { return velocity; };

	void setFlipped(bool f){isFlipped = f;}
	bool getFlipped() { return isFlipped; };

	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect box) { collisionBox = box; };
	sf::FloatRect getCollisionBox();
	void setCollider(bool c) { collider = c; };
	bool getCollider() { return collider; };

	void setInput(Input* i) { input = i; };
	void setWindow(sf::RenderWindow* w) { window = w; };

	void addComponent(std::shared_ptr<Component> component) { components.push_back(component); };
	//std::shared_ptr<Component> getComponent();
	bool IsPlayer() { return isPlayer; };
	void setPlayer(bool p) { isPlayer = p; };

	bool IsCharacter() { return isChar; };
	void setCharacter(bool c) { isChar = c; };

	bool IsBarrier() { return isBar; };
	void setBarrier(bool b) { isBar = b; };

	int getHealth() { return health; };
	void setHealth(int hp) { health = hp; };
	void takeDamage(int dmg);
	void setHPVisuals(sf::Texture* tex, float px, float py, float sx, float sy, float r)
	{
		hpTexture = tex;
		hpPos = sf::Vector2f(px, py);
		hpSca = sf::Vector2f(sx, sy);
		hpRotat = r;
	};

	Input* input;
	sf::RenderWindow* window;

	sf::Texture* hpTexture;
	sf::Vector2f hpPos, hpSca;
	float hpRotat;

protected:
	bool isPlayer = false;
	bool isChar = false;
	bool isBar = false;
	bool alive = false;
	bool hurt = false;
	int health = 3;
	std::string tag;
	sf::Vector2f velocity;
	bool isFlipped;

	sf::FloatRect collisionBox;
	bool collider;

	sf::Texture texture;

	std::vector<std::shared_ptr<Component>> components;
};

