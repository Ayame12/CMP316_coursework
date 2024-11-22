#pragma once
enum class State { MENU, LEVEL, PAUSE, CREDITS };

class GameState
{
public:
	// Set the current state
	void setCurrentState(State cState);
	// Returns the current state.
	State getCurrentState();

protected:
	State currentState;
};
