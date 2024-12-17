#include "pch.h"
#include "Engine.h"
#include "Scene.h"
Engine::Engine() : 
	scene{nullptr}
{
}

void Engine::Initialize()
{
	std::cout << "Initializing engine..." << std::endl;
}

void Engine::Run()
{
	sf::RenderWindow window(sf::VideoMode(1200, 675), "Game Engine");
	Input input;
	scene = new Scene(&window, &input);

	sf::Clock clock;
	float deltaTime;

	while (window.isOpen()) {
		WindowProcess(&window, &input);
		deltaTime = clock.restart().asSeconds();
		deltaTime /= 2.0f;
		HandleInput(deltaTime);
		Update(deltaTime);
		Render(&window);

	}
}

void Engine::HandleInput(float dt)
{
	scene->handleInput(dt);
}

void Engine::Update(float dt)
{
	scene->update(dt);
}

void Engine::Render(sf::RenderWindow* window)
{
	window->clear(sf::Color(100, 149, 237));

	scene->render();

	window->display();
}

void Engine::WindowProcess(sf::RenderWindow* window, Input* in)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::Resized:
			window->setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
			break;
		case sf::Event::KeyPressed:
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				in->setLeftMouse(Input::MouseState::PRESSED);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::PRESSED);
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			break;
		}
	}
}
