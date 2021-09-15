#include "GameWonState.h"
#include "MainMenuState.h"
#include "PlayState.h"

#include "MenuButton.h"

#include "InputHandler.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "Game.h"

#include <iostream>
using namespace std;

const string GameWonState::_gameWonStateID = "gamewon";

void GameWonState::Update()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update();
		if (Game::Instance()->GetStateMachine()->getState()->getStateID() != _gameWonStateID)
			break;
	}
}
void GameWonState::Render()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Draw();
	}
}

bool GameWonState::onEnter()
{
	cout << "Entering 'gamewon' state\n";
	StateParser* stateparser = new StateParser();
	stateparser->ParseState("assets/XML/states.xml", _gameWonStateID, &_gameObjects, &_textureIDlist);
	
	_callbacks.push_back(0);//IDs range from 1+
	_callbacks.push_back(_restart);
	_callbacks.push_back(_menu);
	setCallbacks(_callbacks);

	return true;
}
bool GameWonState::onExit()
{
	cout << "Exiting 'gamewon' state\n";
	for (int i = 0; i < _textureIDlist.size(); i++)
	{
		TextureManager::Instance()->CleanPNG(_textureIDlist[i]);
	}
	InputHandler::Instance()->resetButtons();
	return true;
}

void GameWonState::_restart()
{
	Game::Instance()->GetStateMachine()->changeState(new PlayState());
}
void GameWonState::_menu()
{
	Game::Instance()->GetStateMachine()->changeState(new MainMenuState());
}
void GameWonState::setCallbacks(const vector<Callback>& callbacks)
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