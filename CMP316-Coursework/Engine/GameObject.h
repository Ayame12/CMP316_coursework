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

	void setFlipped(bool f) { isFlipped = f; };
	bool getFlipped() { return isFlipped; };

	void setCollisionBox(float x, float y, float width, float height) { collisionBox = sf::FloatRect(x, y, width, height); };
	void setCollisionBox(sf::FloatRect box) { collisionBox = box; };
	sf::FloatRect getCollisionBox() { return collisionBox; };
	void setCollider(bool c) { collider = c; };
	bool getCollider() { return collider; };

	void setInput(Input* i) { input = i; };
	void setWindow(sf::RenderWindow* w) { window = w; };

	void addComponent(std::shared_ptr<Component> component) { components.push_back(component); };
	//std::shared_ptr<Component> getComponent();

	Input* input;

protected:
	bool alive;
	std::string tag;
	sf::Vector2f velocity;
	bool isFlipped;

	sf::FloatRect collisionBox;
	bool collider;

	sf::Texture texture;

	sf::RenderWindow* window;

	std::vector<std::shared_ptr<Component>> components;
	std::shared_ptr<Component> aliveComp;
};

