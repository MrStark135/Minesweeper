#include "PauseState.h"
#include "MainMenuState.h"

#include "MenuButton.h"

#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateParser.h"

#include <iostream>
using namespace std;

const std::string PauseState::_pauseID = "pause";

void PauseState::Update()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update();
		if (Game::Instance()->GetStateMachine()->getState()->getStateID() != _pauseID)
			break;
	}
}
void PauseState::Render()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Draw();
	}
}

bool PauseState::onEnter()
{
	cout << "Entering 'pause' state\n";
	StateParser* stateparser = new StateParser();
	stateparser->ParseState("assets/XML/states.xml", _pauseID, &_gameObjects, &_textureIDlist);
	_callbacks.push_back(0);
	_callbacks.push_back(_resume);
	_callbacks.push_back(_mainMenu);
	setCallbacks(_callbacks);
	return true;
}
bool PauseState::onExit()
{
	cout << "Exiting 'pause' state\n";
	for (int i = 0; i < _textureIDlist.size(); i++)
	{
		TextureManager::Instance()->CleanPNG(_textureIDlist[i]);
	}
	InputHandler::Instance()->resetButtons();
	return true;
}

void PauseState::_mainMenu()
{
	Game::Instance()->GetStateMachine()->changeState(new MainMenuState());
}
void PauseState::_resume()
{
	Game::Instance()->GetStateMachine()->popState();
}
void PauseState::setCallbacks(const vector<Callback>& callbacks)
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