#include "Engine.h"
#include "ObjectMaker.h"
#include <iostream>

int main() {

	Object o;
	o.setTag("hand");
	o.setPosition(1, 1) ;
	o.setScale(20, 20);
	o.setSpeed(500);
	o.setTexture("res/animationTest.png", true);
	o.setAnimation(ANIMATION_TYPES::IDLE, 0, 0, 4, 4, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_VER, 0, 4, 4, 4, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_HOR, 0, 8, 4, 4, 4, 0.2, true);
	o.setMovementBehaviour(MOVEMENT_TYPES::PLAYER_CONTROL);
	o.setAttackType(1, ATTACK_TYPES::PROJECTILE_STRAIGHT);
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::TIMER);
	o.setAttackKey(1, 2);
	o.setAttackDirection(1, ATTACK_DIRECTION_CONTROLL::MOUSE);
	o.setAttackScale(1, 1, 1);
	o.setAttackSpeed(1, 2500);
	o.setAttackCoolDown(1, 0.1);
	o.writeObject();
	o.finishLevel();

	o.setTag("test");
	o.setPosition(100, 100);
	o.setScale(0.04, 0.04);
	o.setTexture("res/facelessvoid.png", false);
	o.setSpeed(200);
	o.setMovementBehaviour(MOVEMENT_TYPES::PATROL);
	o.addPatrollPoint(10, 30);
	o.addPatrollPoint(100, 30);
	o.setFollowTarget("hand", 200);
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