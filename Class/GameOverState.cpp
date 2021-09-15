#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"

#include "MenuButton.h"

#include "InputHandler.h"
#include "TextureManager.h"
#include "StateParser.h"
#include "Game.h"

#include <iostream>
using namespace std;

const string GameOverState::_gameOverStateID = "gameover";

void GameOverState::Update()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update();
		if (Game::Instance()->GetStateMachine()->getState()->getStateID() != _gameOverStateID)
			break;
	}
}
void GameOverState::Render()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Draw();
	}
}

bool GameOverState::onEnter()
{
	cout << "Entering 'gameover' state\n";
	StateParser* stateparser = new StateParser();
	stateparser->ParseState("assets/XML/states.xml", _gameOverStateID, &_gameObjects, &_textureIDlist);
	_callbacks.push_back(0);
	_callbacks.push_back(_restart);
	_callbacks.push_back(_menu);
	setCallbacks(_callbacks);
	return true;
}
bool GameOverState::onExit()
{
	cout << "Exiting 'gameover' state\n";
	for (int i = 0; i < _textureIDlist.size(); i++)
	{
		TextureManager::Instance()->CleanPNG(_textureIDlist[i]);
	}
	InputHandler::Instance()->resetButtons();
	return true;
}

void GameOverState::_restart()
{
	Game::Instance()->GetStateMachine()->changeState(new PlayState());
}
void GameOverState::_menu()
{
	Game::Instance()->GetStateMachine()->changeState(new MainMenuState());
}
void GameOverState::setCallbacks(const vector<Callback>& callbacks)
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