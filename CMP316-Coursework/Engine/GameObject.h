#pragma once
#include "Input.h"
//enum OBJ_STATE { IDLE, WALK, DEAD, HURT, MELE, RANGE };

//namespace sf {
//	class Vector2f;
//	class RenderWindow;
//	class FloatRect;
//	class Texture;
//}
//class Input;

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

	void setVelocity(sf::Vector2f v) { velocity = v; };
	sf::Vector2f getVelosity() { return velocity; };

	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect box) { collisionBox = box; };
	sf::FloatRect getCollisionBox() { return collisionBox; };
	void setCollider(bool c) { collider = c; };
	bool getCollider() { return collider; };

	void setInput(Input* i) { input = i; };
	void setWindow(sf::RenderWindow* w) { window = w; };

private:
	bool alive;
	sf::Vector2f velocity;

	sf::FloatRect collisionBox;
	bool collider;

	sf::Texture texture;

	Input* input;
	sf::RenderWindow* window;


//	// Control sprite speed and direction
//	void setVelocity(sf::Vector2f vel);
//	void setVelocity(float vx, float vy);
//	sf::Vector2f getVelocity();
//
//	// Sprite state
//	bool isAlive() { return alive; };
//	void setAlive(bool b) { alive = b; };
//
//	// For sprite collision, set collider box, get collider box, and dedicated virtual function for collision response
//	bool isCollider() { return collider; };
//	void setCollider(bool b) { collider = b; };
//	sf::FloatRect getCollisionBox();
//	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
//	void setCollisionBox(sf::FloatRect fr) { collisionBox = fr; };
//	virtual void collisionResponse(GameObject* collider);
//
//	// Set the input component
//	/*void setInput(Input* in) { input = in; };
//	void setWindow(sf::RenderWindow* win) { window = win; };*/
//
//private:
//	// Sprite properties
//	sf::Vector2f velocity;
//	bool alive;
//
//	// Collision vars
//	sf::FloatRect collisionBox;
//	bool collider;
//
//	// input component 
//	//Input* input;
//	sf::RenderWindow* window;

};

