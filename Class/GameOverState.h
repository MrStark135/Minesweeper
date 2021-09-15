#pragma once
#include "GameState.h"
#include "GameObject.h"

#include <vector>

//if a state has buttons it inherits from MenuState
class GameOverState :public GameState
{
public:
	//calls same funcs() of each gameObject
	virtual void Update();
	virtual void Render();

	//when changing to or from this state
	virtual bool onEnter();
	virtual bool onExit();

	//to cmp IDs of states
	virtual std::string getStateID() const { return _gameOverStateID; }

private:

	static const std::string _gameOverStateID;//string identifying the gamestate
	std::vector<GameObject*> _gameObjects;//game objects for play state
	
	//vector of callback funcs()
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	//functions for pause buttons
	static void _restart();
	static void _menu();
};

