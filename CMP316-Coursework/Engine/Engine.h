#pragma once
#include "Input.h"

namespace sf {
	class RenderWindow;
}

class Scene;

class Engine
{
public:
	Engine();
	void Initialize();
	void Run();

private:
	void HandleInput(float dt);
	void Update(float dt);
	void Render(sf::RenderWindow* window);
	void WindowProcess(sf::RenderWindow* window, Input* in);

	Scene* scene;

};

