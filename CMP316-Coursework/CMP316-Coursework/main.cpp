#include "Engine.h"
#include "ObjectMaker.h"
#include <iostream>

int main() {

	Object o;
	o.setTag("hand");
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setPosition(1, 1) ;
	o.setScale(20, 20);
	o.setSpeed(500);
	o.setTexture("res/animationTest.png", true);
	o.setAnimation(ANIMATION_TYPES::IDLE, 0, 0, 4, 4, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_VER, 0, 4, 4, 4, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_HOR, 0, 8, 4, 4, 4, 0.2, true);
	o.setMovementBehaviour(MOVEMENT_TYPES::PLAYER_CONTROL);
	o.setAttackType(1, ATTACK_TYPES::NO_ATTACK);
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::TIMER);
	o.setAttackKey(1, 2);
	o.setAttackDirection(1, ATTACK_DIRECTION_CONTROLL::MOUSE);
	o.setAttackScale(1, 1, 1);
	o.setAttackSpeed(1, 1000);
	o.setAttackCoolDown(1, 0.2);
	o.setAttackDamage(1, 1);
	o.writeObject();
	o.finishLevel();

	o.setTag("bg");
	o.setPosition(0, 0);
	o.setObjType(OBJECT_TYPE::BACKGROUND);
	o.setScale(2, 2);
	o.setTexture("res/image.png", false);
	o.writeObject();

	o.setTag("bg");
	o.setPosition(50, 50);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(10, 10);
	o.setTexture("res/animationTest.png", false);
	o.writeObject();

	o.setTag("test");
	o.setPosition(500, 500);
	o.setHealth(3);
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setScale(0.04, 0.04);
	o.setTexture("res/facelessvoid.png", false);
	o.setSpeed(300);
	o.setMovementBehaviour(MOVEMENT_TYPES::PATROL);
	o.addPatrollPoint(10, 500);
	o.addPatrollPoint(100, 500);
	o.setFollowTarget("hand", 200);
	o.writeObject();

	o.finishLevel();

	o.setTag("2");
	o.setPosition(50, 50);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(0.2, 0.2);
	o.setTexture("res/image.png", false);
	o.writeObject();

	o.setTag("3");
	o.setPosition(500, 500);
	o.setHealth(3);
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setScale(50, 50);
	o.setTexture("res/animationTest.png", false);
	o.setSpeed(300);
	o.setMovementBehaviour(MOVEMENT_TYPES::PATROL);
	o.addPatrollPoint(10, 500);
	o.addPatrollPoint(100, 500);
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