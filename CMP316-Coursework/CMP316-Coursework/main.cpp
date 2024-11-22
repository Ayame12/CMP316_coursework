#include "Engine.h"
#include <iostream>

int main() {


	Input input;
	Engine engine;
	//Test();
	engine.Initialize();
	//Run();
	while (true) {
		if (input.GetSFKey(0)) 
		{
			std::cout << "A pressed\n";
		}
	}
	return 0;
}