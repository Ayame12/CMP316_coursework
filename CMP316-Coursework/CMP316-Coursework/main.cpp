#include "Engine.h"
#include "ObjectMaker.h"
#include <iostream>

int main() {

	Object o;
	o.setTag("hand");
	o.setPosition(1, 1) ;
	o.setScale(1, 1);
	o.setSpeed(500);
	o.setTexture("res/image.png", false);
	o.writeObject();

	o.setTag("test");
	o.setPosition(10, 10);
	o.setTexture("res/image.png", false);
	o.writeObject();
	o.finishLevel();

	Input input;
	Engine engine;
	//Test();
	engine.Initialize();
	engine.Run();
	/*while (true) {
		if (input.GetSFKey(0)) 
		{
			std::cout << "A pressed\n";
		}
	}*/
	return 0;
}