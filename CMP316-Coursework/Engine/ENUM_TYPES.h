#pragma once

enum OBJECT_TYPE { ACTOR, BACKGROUND, TERRAIN, UI, TRIGGER, NONE };
enum TRIGGER_ACTION_TYPE { LOAD_NEXT_LVL, ENTER_NEXT_LVL, NO_ACTION };
enum MOVEMENT_TYPES { STATIONARY, PATROOL, FOLLOW, PLAYER_CONTROL };
enum ATTACK_TYPES { PROJECTILE_STRAIGHT, PROJECTILE_TARGETED, MELE, NO_ATTACK };
enum ANIMATION_TYPES { IDLE, WALK, DEATH, ATTACK1, ATTACK2 };
enum ATTACK_CONDITION_TYPES { OBJ_PROXIMITY, TIMER, PLAYER, NO_COND };