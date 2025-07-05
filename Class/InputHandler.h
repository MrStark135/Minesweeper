#pragma once
#include "Vector2D.h"
#include <SDL2/SDL.h>

enum mouseButtons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance();
	void Update();
	void Clean() {};
	void resetButtons();

	//mouse getters
	bool getMouseButtonState(int buttonNumber);
	Vector2D* getMousePosition();

	//keyboard state checker
	bool isKeyDown(SDL_Scancode key);
private:
	static InputHandler* _instance;
	InputHandler()
		: _mousePosition(new Vector2D(0, 0)) {};
	~InputHandler() {};

	//for mouse
	bool _mouseButtonStates[3];
	Vector2D* _mousePosition;
	//handle mouse events
	void onMouseButtonDown(SDL_Event event1);
	void onMouseButtonUp(SDL_Event event1);
	void onMouseMotion(SDL_Event event1);

	//for keyboard
	const uint8_t* _keystates;
	//handle keyboard events
	/*create a function later if required*/
};

