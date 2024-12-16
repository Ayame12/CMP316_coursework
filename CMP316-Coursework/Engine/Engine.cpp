#include "pch.h"
#include "Engine.h"
#include "Scene.h"
Engine::Engine() : 
	scene{nullptr}
{
}

void Engine::Initialize()
{
	// Any engine-wide initialization, like loading assets or setting up systems
	std::cout << "Initializing engine..." << std::endl;
	//SoLoud::Soloud core;
	// Placeholder: Later you might initialize asset managers, load textures, etc.
}

void Engine::Run()
{
	// Run the game loop
	sf::RenderWindow window(sf::VideoMode(1200, 675), "Game Engine");
	Input input;
	scene = new Scene(&window, &input);

	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;

	while (window.isOpen()) {
		WindowProcess(&window, &input);
		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();
		deltaTime /= 2.0f;
		// Call standard game loop functions (input, update and render)
		HandleInput(deltaTime);
		Update(deltaTime);
		Render(&window);

		// Update input class, handle pressed keys
		// Must be done last.
		/*input.update();*/
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
	// Handle window events.
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
			// update input class
			in->setKeyDown(event.key.code);
			break;
		case sf::Event::KeyReleased:
			//update input class
			in->setKeyUp(event.key.code);
			break;
		case sf::Event::MouseMoved:
			//update input class
			in->setMousePosition(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//update input class
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
				//update input class
				in->setLeftMouse(Input::MouseState::UP);
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				in->setRightMouse(Input::MouseState::UP);
			}
			break;
		default:
			// don't handle other events
			break;
		}
	}
}
