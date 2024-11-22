#pragma once
#include "Input.h"

namespace sf {
	class RenderWindow;
}

class Engine
{
public:
	void Initialize();
	void Run();

private:
	void HandleInput(float dt);
	void Update(float dt);
	void Render();
	void WindowProcess(sf::RenderWindow* window, Input* in);
};

