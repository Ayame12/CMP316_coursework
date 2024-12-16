#include "Engine.h"
#include "ObjectMaker.h"
#include <iostream>
#include "MenuMaker.h"

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

	MenuMaker m;
	
	// Create the Main Menu
	m.setMenuType(MENU_TYPE::MAIN);            // Set type to MAIN
	m.setBgTexture("main_menu_bg.png");        // Set background texture
	m.setTitleText("Main Menu");               // Set title text
	m.setTitleXPos(100.0f);                    // Set title X position
	m.setTitleYPos(50.0f);                     // Set title Y position
	m.setBGXScale(1.5f);                       // Set background X scale
	m.setBGYScale(1.5f);                       // Set background Y scale
	m.setTextXSize(24.0f);                     // Set title text X size
	m.setTextYSize(24.0f);                     // Set title text Y size

	// Add buttons for the Main Menu
	m.setButtonXPos(200.0f);                   // Button 1 X position
	m.setButtonYPos(300.0f);                   // Button 1 Y position
	m.setButtonText("Start Game");             // Button 1 text
	m.setButtonNormalTexture("btn_norm.png");  // Button 1 normal texture
	m.setButtonHighlightTexture("btn_high.png"); // Button 1 highlight texture
	m.setLevelToTarget(1);                     // Button 1 level target
	m.setButtonXScale(1.0f);                   // Button 1 X scale
	m.setButtonYScale(1.0f);                   // Button 1 Y scale

	m.setButtonXPos(200.0f);                   // Button 2 X position
	m.setButtonYPos(400.0f);                   // Button 2 Y position
	m.setButtonText("Exit Game");              // Button 2 text
	m.setButtonNormalTexture("btn_norm.png");  // Button 2 normal texture
	m.setButtonHighlightTexture("btn_high.png"); // Button 2 highlight texture
	m.setLevelToTarget(1);                    // Button 2 level target (exit)
	m.setButtonXScale(1.0f);                   // Button 2 X scale
	m.setButtonYScale(1.0f);                   // Button 2 Y scale

	// Create the Pause Menu
	m.setMenuType(MENU_TYPE::PAUSE);           // Set type to PAUSE
	m.setBgTexture("pause_menu_bg.png");       // Set background texture
	m.setTitleText("Pause Menu");              // Set title text
	m.setTitleXPos(150.0f);                    // Set title X position
	m.setTitleYPos(80.0f);                     // Set title Y position
	m.setBGXScale(1.2f);                       // Set background X scale
	m.setBGYScale(1.2f);                       // Set background Y scale
	m.setTextXSize(20.0f);                     // Set title text X size
	m.setTextYSize(20.0f);                     // Set title text Y size

	// Add buttons for the Pause Menu
	m.setButtonXPos(250.0f);                   // Button 1 X position
	m.setButtonYPos(300.0f);                   // Button 1 Y position
	m.setButtonText("Resume Game");            // Button 1 text
	m.setButtonNormalTexture("btn_norm.png");  // Button 1 normal texture
	m.setButtonHighlightTexture("btn_high.png"); // Button 1 highlight texture
	m.setLevelToTarget(1);                     // Button 1 level target (resume current level)
	m.setButtonXScale(1.0f);                   // Button 1 X scale
	m.setButtonYScale(1.0f);                   // Button 1 Y scale

	m.setButtonXPos(250.0f);                   // Button 2 X position
	m.setButtonYPos(400.0f);                   // Button 2 Y position
	m.setButtonText("Main Menu");              // Button 2 text
	m.setButtonNormalTexture("btn_norm.png");  // Button 2 normal texture
	m.setButtonHighlightTexture("btn_high.png"); // Button 2 highlight texture
	m.setLevelToTarget(1);                     // Button 2 level target (go back to main menu)
	m.setButtonXScale(1.0f);                   // Button 2 X scale
	m.setButtonYScale(1.0f);                   // Button 2 Y scale

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