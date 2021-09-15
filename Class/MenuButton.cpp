#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton()
	:SDLGameObject() {}

void MenuButton::Draw()
{
	SDLGameObject::Draw();
}
void MenuButton::Update()
{
	Vector2D* mousePos = InputHandler::Instance()->getMousePosition();
	int x = mousePos->getX(), y = mousePos->getY();
	if (x > _position.getX() && x < _position.getX() + _width && y > _position.getY() && y < _position.getY() + _height)
	{
		_currentFrame = MOUSE_OVER;
		if(_clicked  && !InputHandler::Instance()->getMouseButtonState(LEFT)) _callback();
		if (InputHandler::Instance()->getMouseButtonState(LEFT))
		{
			_currentFrame = CLICKED;
			_clicked = true;
		}
		else 
		{
			_clicked = false;
			_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		_currentFrame = MOUSE_OUT;
		_clicked = false;
	}
}
void MenuButton::Clean()
{
	SDLGameObject::Clean();
}

void MenuButton::Load(const LoaderParams* params)
{
	SDLGameObject::Load(params);
	_callbackID = params->getCallbackID();
}