//game states required for functions that change the state
#include "PlayState.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "GameWonState.h"
//MenuButton Class
#include "MenuButton.h"
//singletons for rendering and accessing stuff
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"
//for printing to the console
#include <iostream>
using namespace std;

const string PlayState::_playStateID = "play";

void PlayState::Update()
{
	_mineField.Update();
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update();
	}
	if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance()->GetStateMachine()->pushState(new PauseState());
	}
}
void PlayState::Render()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Draw();
	}
	_mineField.Draw();

	if (_mineField.getMineHit())
	{
		_mineField.gameOverAnim();
		Game::Instance()->GetStateMachine()->changeState(new GameOverState());
	}
	else if (_mineField.getGameWon())
	{
		_mineField.gameWonAnim();
		Game::Instance()->GetStateMachine()->changeState(new GameWonState());
	}
}

bool PlayState::onEnter()
{
	cout << "Entering 'play' state\n";

	int width, height, numMines, offsetX, offsetY;
	StateParser* stateparser = new StateParser();
	stateparser->ParseState("assets/XML/states.xml", _playStateID, &_gameObjects, &_textureIDlist);
	stateparser->parseParams("assets/XML/states.xml", width, height, numMines, offsetX, offsetY);
	_mineField = MineField(width, height, numMines, offsetX, offsetY);

	_callbacks.push_back(0);
	_callbacks.push_back(_pause);//id 1
	setCallbacks(_callbacks);

	_hold = false;//reset click

	return true;
}
bool PlayState::onExit()
{
	cout << "Exiting 'play' state\n";
	for (int i = 0; i < _textureIDlist.size(); i++)
	{
		TextureManager::Instance()->CleanPNG(_textureIDlist[i]);
	}
	InputHandler::Instance()->resetButtons();
	return true;
}

void PlayState::_pause()
{
	Game::Instance()->GetStateMachine()->pushState(new PauseState());
}
void PlayState::setCallbacks(const vector<Callback>& callbacks)
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(_gameObjects[i]))
		{
			MenuButton* button = dynamic_cast<MenuButton*>(_gameObjects[i]);
			button->setCallback(_callbacks[button->getCallbackID()]);
		}
	}
}
