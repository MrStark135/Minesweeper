#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include "MineField.h"

#include <vector>

class PlayState :public GameState
{
public:
	virtual void Update();
	virtual void Render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return _playStateID; }
private:
	//string identifying the gamestate
	static const std::string _playStateID;
	std::vector<GameObject*> _gameObjects;
	//mine field contains IDs of displayed tiles
	MineField _mineField;

	//to enable clicky behaviour
	bool _hold;

	//vector of callback funcs()
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	//functions for pause buttons
	static void _pause();
};

