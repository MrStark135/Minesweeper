#include <SDL.h>
#include <iostream>
using namespace std;
#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::_instance;
InputHandler* InputHandler::Instance()
{
	if (_instance == 0)
	{
		_instance = new InputHandler();
	}
	return _instance;
}

void InputHandler::Update()
{
	//update keyboard
	_keystates = SDL_GetKeyboardState(0);
	SDL_Event event1;
	while (SDL_PollEvent(&event1))
	{
		switch (event1.type)
		{
		case SDL_QUIT:
		{
			cout << "Quitting...\n";
			Game::Instance()->Clean();
			break;
		}
		case SDL_KEYUP: case SDL_KEYDOWN:
		{
			_keystates = SDL_GetKeyboardState(0);
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			onMouseButtonDown(event1);
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			onMouseButtonUp(event1);
			break;
		}
		case SDL_MOUSEMOTION:
		{
			onMouseMotion(event1);
			break;
		}
		default: break;
		}
	}
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
	return _mouseButtonStates[buttonNumber];
}
Vector2D* InputHandler::getMousePosition()
{
	return _mousePosition;
}
void InputHandler::onMouseButtonDown(SDL_Event event1)
{
	if (event1.button.button == SDL_BUTTON_LEFT)
	{
		_mouseButtonStates[LEFT] = true;
	}
	else if (event1.button.button == SDL_BUTTON_RIGHT)
	{
		_mouseButtonStates[RIGHT] = true;
	}
	else if (event1.button.button == SDL_BUTTON_MIDDLE)
	{
		_mouseButtonStates[MIDDLE] = true;
	}
}
void InputHandler::onMouseButtonUp(SDL_Event event1)
{
	if (event1.button.button == SDL_BUTTON_LEFT)
	{
		_mouseButtonStates[LEFT] = false;
	}
	else if (event1.button.button == SDL_BUTTON_RIGHT)
	{
		_mouseButtonStates[RIGHT] = false;
	}
	else if (event1.button.button == SDL_BUTTON_MIDDLE)
	{
		_mouseButtonStates[MIDDLE] = false;
	}
}
void InputHandler::onMouseMotion(SDL_Event event1)
{
	_mousePosition->setX(event1.motion.x);
	_mousePosition->setY(event1.motion.y);
}
void InputHandler::resetButtons()
{
	_mouseButtonStates[LEFT] = false;
	_mouseButtonStates[MIDDLE] = false;
	_mouseButtonStates[RIGHT] = false;
}
bool InputHandler::isKeyDown(SDL_Scancode key)
{
	if (_keystates != 0)
	{
		if (_keystates[key] != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}