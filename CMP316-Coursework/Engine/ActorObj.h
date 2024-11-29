#pragma once
#include "GameObject.h"

enum OBJ_STATE { IDLE, WALK, DEAD, HURT, MELE, RANGE };

class ActorObj : public GameObject
{
public:
	ActorObj();
	~ActorObj();

	void handleInput(float dt);
	void update(float dt);

	void setIsPlayer(bool p) { isPlayer = p; };
	void setMovementControlls(int up, int dowm, int left, int right);
	std::vector<int>* getControllsVctor() { return &controlls; };

private:
	bool isPlayer;
	std::vector<int> controlls;


};

