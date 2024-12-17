#include "pch.h"
#include "MenuObject.h"
#include "Level.h"

//based on the target a menu object (button) has it will change the game state accordingly
//there is a small timer to prevent the spamming of commands that happens due to the input from the keyboard
//lasting several ticks
void MenuObject::handleInput(float dt)
{
	if (swappedIn)
	{
		swappedTimer += dt;
	}
	if (swappedTimer >= maxTimer)
	{
		swappedTimer = 0;
		swappedIn = false;
	}
	if (isSelected && input->isPressed(sf::Keyboard::Key::Space) && !swappedIn)
	{
		nextButton->isSelected = true;
		nextButton->swappedIn = true;
		isSelected = false;
	}
	if (isSelected && input->isPressed(sf::Keyboard::Key::Enter))
	{
		pressed = true;
	}
}

//after button was pressed the game state is altered
void MenuObject::update(float dt)
{
	if (isSelected)
	{
		setTexture(HighTex);
	}
	else
	{
		setTexture(NormalTex);
	}
	if (pressed)
	{
		if (target == -2)
		{
			window->close();
		}
		else if (target == -1)
		{
			*gState = GAME_STATE::LEVEL;
		}
		else if (target == 0)
		{
			*gState = GAME_STATE::MENU;
		}
		else
		{
			lvl->loadLevel(target);
			lvl->switchLevel();
			*gState = GAME_STATE::LEVEL;
		}
		pressed = false;
	}
}
