#pragma once
#include "GameState.h"
#include <vector>
using namespace std;

class GameStateMachine
{
public:
	//switching states
	void pushState(GameState* state);
	void changeState(GameState* state);
	void popState();
	//update & render the current state
	void Update();
	void Render();
	//getCurrentState
	GameState* getState() { return _gameStates.back(); }
private:
	vector<GameState*> _gameStates;
};

