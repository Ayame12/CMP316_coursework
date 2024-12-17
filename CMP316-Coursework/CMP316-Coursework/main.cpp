#include "Engine.h"
#include "ObjectMaker.h"
#include <iostream>
#include "MenuMaker.h"

Object o;

void makeFollowEnemy(float x, float y, std::string tag)
{
	o.setTag(tag);
	o.setPosition(x, y);
	o.setHealth(3);
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setScale(2.5, 2.5);
	o.setTexture("res/playerAnimationDemo.png", true);
	o.setAnimation(ANIMATION_TYPES::IDLE, 0, 0, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_DOWN, 0, 48 * 3, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_UP, 0, 48 * 2, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_HOR, 0, 48, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::HURT, 0, 48 * 4, 48, 48, 4, 0.2, true);
	o.setSpeed(300);
	o.setMovementBehaviour(MOVEMENT_TYPES::FOLLOW);
	o.setAttackType(1, ATTACK_TYPES::PROJECTILE_TARGETED);
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::TIMER);
	o.setAttackMeleTimer(1, 0.5);
	//o.setAttackOffset(1, 300, 0);
	o.setAttackTexture(1, "res/redAttack.png");
	o.setAttackTaget(1, "player", 0);
	o.setAttackScale(1, 5, 5);
	o.setAttackSpeed(1, 1000);
	o.setAttackCoolDown(1, 0.2);
	o.setAttackDamage(1, 1);
	o.setFollowTarget("player", 200);
	o.writeObject();


	/*o.setSpeed(300);
	o.setMovementBehaviour(MOVEMENT_TYPES::PATROL);
	o.setAttackType(1, ATTACK_TYPES::MELE);
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::OBJ_PROXIMITY);
	o.setAttackProximity(1, "player", 300);
	o.setAttackMeleTimer(1, 0.2);
	o.setAttackTexture(1, "res/redBeam.png");
	o.setAttackScale(1, 5, 5);
	o.setAttackCoolDown(1, 0.2);
	o.setAttackDamage(1, 1);
	o.addPatrollPoint(100, 400);
	o.addPatrollPoint(300, 400);*/

	//o.setSpeed(300);
	//o.setMovementBehaviour(MOVEMENT_TYPES::FOLLOW);
	//o.setAttackType(1, ATTACK_TYPES::MELE);
	//o.setAttackCondition(1, ATTACK_CONDITION_TYPES::OBJ_PROXIMITY);
	//o.setAttackMeleTimer(1, 0.5);
	////o.setAttackOffset(1, 300, 0);
	//o.setAttackProximity(1, "player", 300);
	//o.setAttackTexture(1, "res/redBeam.png");
	//o.setAttackTaget(1, "player", 0);
	//o.setAttackScale(1, 5, 5);
	//o.setAttackSpeed(1, 1000);
	//o.setAttackCoolDown(1, 0.2);
	//o.setAttackDamage(1, 1);
	//o.setFollowTarget("player", 200);
	//o.writeObject();
}

int main() {

	o.setTag("player");
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setPosition(20, 20);
	o.setScale(2, 2);
	o.setSpeed(700);
	o.setTexture("res/enemyAnimationDemo.png", true);
	o.setAnimation(ANIMATION_TYPES::IDLE, 0, 0, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_DOWN, 0, 48*3, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_UP, 0, 48*2, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_HOR, 0, 48, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::HURT, 0, 48*4, 48, 48, 4, 0.2, true);
	o.setHealth("res/heart.png", 550, 300, 1, 1, 0);
	o.setMovementBehaviour(MOVEMENT_TYPES::PLAYER_CONTROL);
	o.setAttackType(1, ATTACK_TYPES::PROJECTILE_STRAIGHT);
	o.setAttackTexture(1, "res/playerProjectile.png");
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::TIMER);
	o.setAttackDirection(1, ATTACK_DIRECTION_CONTROLL::MOUSE);
	o.setAttackScale(1, 5, 5);
	o.setAttackSpeed(1, 1000);
	o.setAttackCoolDown(1, 0.2);
	o.setAttackDamage(1, 1);
	o.writeObject();
	o.finishLevel();

	o.setTag("bg");
	o.setPosition(-2000, -1000);
	o.setObjType(OBJECT_TYPE::BACKGROUND);
	o.setScale(10, 10);
	o.setTexture("res/levelBG.png", false);
	o.writeObject();

	o.setTag("barrier");
	o.setPosition(50, 50);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(10, 10);
	o.setTexture("res/barrier.png", false);
	o.writeObject();

	float xPos[5] = { 200,300,250,300,150 };
	float yPos[5] = { 200,300,300,250,200 };

	for (int i = 0; i < 5; i++)
	{
		makeFollowEnemy(xPos[i], yPos[i], "followEnemy" + std::to_string(i));
	}

	o.finishLevel();

	o.setTag("bg");
	o.setPosition(-2000, -1000);
	o.setObjType(OBJECT_TYPE::BACKGROUND);
	o.setScale(10, 10);
	o.setTexture("res/controlsBGss.png", false);
	o.writeObject();

	o.setTag("barrier");
	o.setPosition(100, 0);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(10, 10);
	o.setTexture("res/barrier.png", false);
	o.writeObject();

	o.setTag("barrier2");
	o.setPosition(300, 0);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(10, 10);
	o.setTexture("res/barrier.png", false);
	o.writeObject();

	o.setTag("barrier3");
	o.setPosition(500, 0);
	o.setObjType(OBJECT_TYPE::TERRAIN);
	o.setScale(10, 10);
	o.setTexture("res/barrier.png", false);
	o.writeObject();

	o.setTag("turretish");
	o.setPosition(200, 400);
	o.setHealth(5);
	o.setObjType(OBJECT_TYPE::ACTOR);
	o.setScale(2.5, 2.5);
	o.setTexture("res/playerAnimationDemo.png", true);
	o.setAnimation(ANIMATION_TYPES::IDLE, 0, 0, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_DOWN, 0, 48 * 3, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_UP, 0, 48 * 2, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::WALK_HOR, 0, 48, 48, 48, 4, 0.2, true);
	o.setAnimation(ANIMATION_TYPES::HURT, 0, 48 * 4, 48, 48, 4, 0.2, true);
	o.setSpeed(300);
	o.setMovementBehaviour(MOVEMENT_TYPES::PATROL);
	o.setAttackType(1, ATTACK_TYPES::PROJECTILE_STRAIGHT);
	o.setAttackSpeed(1, 500);
	o.setProjectileNumber(1, 4, 90);
	o.setAttackDirection(1, 0, 0);
	o.setAttackCondition(1, ATTACK_CONDITION_TYPES::TIMER);
	o.setAttackProximity(1, "player", 300);
	o.setAttackMeleTimer(1, 0.2);
	o.setAttackTexture(1, "res/redBeam.png");
	o.setAttackScale(1, 5, 5);
	o.setAttackCoolDown(1, 0.2);
	o.setAttackDamage(1, 1);
	o.addPatrollPoint(100, 400);
	o.addPatrollPoint(200, 300);
	o.addPatrollPoint(300, 200);
	o.addPatrollPoint(400, 300);
	o.addPatrollPoint(500, 400);

	o.writeObject();

	o.finishLevel();

	o.finished();

	MenuMaker m;
	
	m.setMenuType(MENU_TYPE::MAIN);
	m.setBgTexture("res/background2.0.png");
	m.setTitleText("Main Menu");
	m.setTitleXPos(-90);
	m.setTitleYPos(-50);
	m.setBGXScale(10);
	m.setBGYScale(10);
	m.setFontSize(60);
	m.setTextScale(1);
	m.setBGXPos(50);
	m.setBGYPos(20);

	m.setButtonXPos(60);
	m.setButtonYPos(100);
	m.setButtonText("Start Game");
	m.setButtonNormalTexture("res/buttonHigh.png");
	m.setButtonHighlightTexture("res/nuttonNor.png");
	m.setLevelToTarget(1);
	m.setButtonFontSize(35);
	m.setButtonTextScale(1);
	m.setButonXScale(3);
	m.setButonYScale(3);
	m.setbutoonTextPos(-30, 80);

	m.setButtonXPos(60);
	m.setButtonYPos(220);
	m.setButtonText("Exit Game");
	m.setButtonNormalTexture("res/buttonHigh.png");
	m.setButtonHighlightTexture("res/nuttonNor.png");
	m.setLevelToTarget(-2);
	m.setButtonFontSize(38);
	m.setButtonTextScale(1);
	m.setButonXScale(3);
	m.setButonYScale(3);
	m.setbutoonTextPos(-30, 195);

	m.setMenuType(MENU_TYPE::PAUSE);
	m.setBgTexture("res/controlsBG.png");
	m.setTitleText("Pause Menu");
	m.setTitleXPos(-100);
	m.setTitleYPos(-190);
	m.setBGXScale(10);
	m.setBGYScale(10);
	m.setFontSize(60);
	m.setTextScale(1);
	m.setBGXPos(50);
	m.setBGYPos(20);

	m.setButtonXPos(60);
	m.setButtonYPos(50);
	m.setButtonText("Resume Game");
	m.setButtonNormalTexture("res/buttonHigh.png");
	m.setButtonHighlightTexture("res/nuttonNor.png");
	m.setLevelToTarget(-1);
	m.setButtonFontSize(27);
	m.setButtonTextScale(1);
	m.setButonXScale(3);
	m.setButonYScale(3);
	m.setbutoonTextPos(-30, 30);

	m.setButtonXPos(20000);
	m.setButtonYPos(20000);
	m.setButtonText("filler");
	m.setButtonNormalTexture("res/buttonHigh.png");
	m.setButtonHighlightTexture("res/nuttonNor.png");
	m.setLevelToTarget(0);
	m.setButtonFontSize(38);
	m.setButtonTextScale(1);
	m.setButonXScale(3);
	m.setButonYScale(3);
	m.setbutoonTextPos(20000, 20000);

	m.writeMenus();



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