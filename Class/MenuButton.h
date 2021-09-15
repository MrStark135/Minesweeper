#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class MenuButton :public SDLGameObject
{
public:
	MenuButton();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	virtual void Load(const LoaderParams* params);
	void setCallback(void(*callback)()) { _callback = callback; }
	int getCallbackID() const { return _callbackID; }
private:
	void(*_callback)();
	int _callbackID;
	//states of mouse, for code readability
	bool _clicked;
	enum buttonState
	{
		MOUSE_OUT = 1,
		MOUSE_OVER = 2,
		CLICKED = 3
	};
};

class MenuButtonCreator :public BaseCreator
{
public:
	GameObject* createGameObject() const
	{
		return new MenuButton();
	}
};