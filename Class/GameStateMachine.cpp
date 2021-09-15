#include "GameStateMachine.h"

//switching states functions
void GameStateMachine::pushState(GameState* state)
{
	_gameStates.push_back(state);
	_gameStates.back()->onEnter();
}
void GameStateMachine::changeState(GameState* state)
{
	if (!_gameStates.empty())
	{
		if (_gameStates.back()->getStateID() == state->getStateID())
		{
			return;
		}
		if (_gameStates.back()->onExit())
		{
			delete _gameStates.back();
			_gameStates.pop_back();
		}
	}
	_gameStates.push_back(state);
	_gameStates.back()->onEnter();
}
void GameStateMachine::popState()
{
	if (!_gameStates.empty())
	{
		if (_gameStates.back()->onExit())
		{
			delete _gameStates.back();
			_gameStates.pop_back();
		}
	}
}

//Update & Render functions
void GameStateMachine::Update()
{
	if (!_gameStates.empty())
	{
		_gameStates.back()->Update();
	}
}
void GameStateMachine::Render()
{
	if (!_gameStates.empty())
	{
		_gameStates.back()->Render();
	}
}