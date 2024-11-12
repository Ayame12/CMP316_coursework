#pragma once
#include "framework.h"

//void Test();
void Initialize();
void Run();

void HandleInput(float dt);
void Update(float dt);
void Render();
void WindowProcess(sf::RenderWindow* window/*, Input* in*/);