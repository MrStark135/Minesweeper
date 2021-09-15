//game states
#include "MainMenuState.h"
#include "PlayState.h"
//for buttons on menu screen
#include "MenuButton.h"
//singletons managing the game rendering
#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
//for console view
#include <iostream>
using namespace std;

const string MainMenuState::_menuID = "mainmenu";

void MainMenuState::Update()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update();
		if (Game::Instance()->GetStateMachine()->getState()->getStateID() != _menuID)
			break;
	}
}
void MainMenuState::Render()
{
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Draw();
	}
}

bool MainMenuState::onEnter()
{	
	cout << "Entering 'mainmenu' state\n";
	StateParser* stateparser = new StateParser();
	stateparser->ParseState("assets/XML/states.xml", _menuID, &_gameObjects, &_textureIDlist);
	_callbacks.push_back(0);
	_callbacks.push_back(_menuPlay);
	_callbacks.push_back(_menuExit);
	setCallbacks(_callbacks);
	return true;
}
bool MainMenuState::onExit()
{
	for (int i = 0; i < _textureIDlist.size(); i++)
	{
		TextureManager::Instance()->CleanPNG(_textureIDlist[i]);
	}
	cout << "Exiting 'mainmenu' state\n";
	return true;
}

void MainMenuState::_menuPlay()
{
	Game::Instance()->GetStateMachine()->changeState(new PlayState());
}
void MainMenuState::_menuExit()
{
	cout << "Quitting...\n";
	Game::Instance()->Clean();
}

void MainMenuState::setCallbacks(const vector<Callback>& callbacks)
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