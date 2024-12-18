#pragma once

//enums that help remember all the types of attacks and objects that can be made by the user

enum OBJECT_TYPE { ACTOR, BACKGROUND, TERRAIN, NONE };
enum MOVEMENT_TYPES { STATIONARY, PATROL, FOLLOW, PLAYER_CONTROL };
enum ATTACK_TYPES { PROJECTILE_STRAIGHT, PROJECTILE_TARGETED, MELE, NO_ATTACK };
enum ANIMATION_TYPES { NOT_PRESENT, IDLE, WALK_UP, WALK_DOWN, WALK_HOR, HURT};
enum ATTACK_CONDITION_TYPES { OBJ_PROXIMITY, TIMER, PLAYER, NO_COND };
enum ATTACK_DIRECTION_CONTROLL { MOUSE, KEYBOARD, NO_CONTROL };