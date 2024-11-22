#include "pch.h"
#include "GameState.h"

// Set the current state
void GameState::setCurrentState(State state)
{
	currentState = state;
}

// Returns the current state.
State GameState::getCurrentState()
{
	return currentState;
}