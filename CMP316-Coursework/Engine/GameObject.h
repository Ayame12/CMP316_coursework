#pragma once
#include "Input.h"
#include <vector>
#include <memory>
#include "Component.h"

//general purpose object that in combination with components will be the base for any 'thing' present in the scene

class GameObject : public sf::RectangleShape
{
public:
	GameObject();
	~GameObject();

	virtual void handleInput(float dt);
	virtual void update(float dt);

	//alive variable allows the scene to know which objects to update or draw and which not to
	void setAlive(bool s) { alive = s; };
	bool isAlive() { return alive; };

	void setTag(std::string t) { tag = t; };

	void setVelocity(sf::Vector2f v) { velocity = v; };
	sf::Vector2f getVelocity() { return velocity; };

	//for animation component
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

	//inportant information for when deciding the result of a collision
	bool IsPlayer() { return isPlayer; };
	void setPlayer(bool p) { isPlayer = p; };
	bool IsCharacter() { return isChar; };
	void setCharacter(bool c) { isChar = c; };
	bool IsBarrier() { return isBar; };
	void setBarrier(bool b) { isBar = b; };

	//used by actor objects
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

	//as this part is not accessed by the user i allowed myself to make a few more variables public than i would normaly deem
//appropriate as the user is technicaly never going to have the chance to mess anything up 

	Input* input;
	sf::RenderWindow* window;

	sf::Texture* hpTexture;
	sf::Vector2f hpPos, hpSca;
	float hpRotat;


	bool hurt = false;

protected:
	bool isPlayer = false;
	bool isChar = false;
	bool isBar = false;
	bool alive = false;
	int health = 3;
	std::string tag;
	sf::Vector2f velocity;
	bool isFlipped;

	sf::FloatRect collisionBox;
	bool collider;

	sf::Texture texture;

	std::vector<std::shared_ptr<Component>> components;
};

