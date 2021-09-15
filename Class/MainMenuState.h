#pragma once
#include "GameState.h"
#include "GameObject.h"

#include <vector>

//if a state has buttons it inherits from MenuState
class MainMenuState :public GameState
{
public:
	//calls same funcs() of each gameObject
	virtual void Update();
	virtual void Render();

	//when changing to or from this state
	virtual bool onEnter();
	virtual bool onExit();

	//to cmp IDs of states
	virtual std::string getStateID() const { return _menuID; }

private:

	static const std::string _menuID;//string identifying the game state
	std::vector<GameObject*> _gameObjects;//menu buttons

	//vector of callback funcs()
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	//functions for buttons
	static void _menuPlay();
	static void _menuExit();
};

