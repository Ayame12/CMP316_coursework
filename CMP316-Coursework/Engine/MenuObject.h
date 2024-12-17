#pragma once
#include "Input.h"
#include "Component.h"
#include <vector>
#include <memory>
#include "GAME_STATES_ENUM.h"

class Level;

//general purpose object that will contain all information abaut the menus

class MenuObject : public sf::RectangleShape
{
public:
	MenuObject() 
	{
		
		input = nullptr;

		setOrigin(0, 0);
		setSize(sf::Vector2f(1, 1));
	};
	~MenuObject() {};

	virtual void handleInput(float dt);
	virtual void update(float dt);

	void setInput(Input* i) { input = i; };
	void setWindow(sf::RenderWindow* w) { window = w; };
	void setLevelAndGS(Level* l, GAME_STATE* gs) { lvl = l; gState = gs; };

	bool pressed = false;
	bool swappedIn = false;;
	float swappedTimer = 0;
	float maxTimer = 0.1;

	MenuObject* nextButton;
	bool isSelected = false;
	sf::Text text;
	sf::Texture* NormalTex;
	sf::Texture* HighTex;
	int target = 1;

	Level* lvl;
	GAME_STATE* gState;

	Input* input;
	sf::RenderWindow* window;
};

