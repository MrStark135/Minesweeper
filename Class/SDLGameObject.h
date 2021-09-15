#pragma once
#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject :public GameObject
{
public:
	SDLGameObject();

	virtual void Draw();
	virtual void Update();
	virtual void Clean() { ; }
	virtual void Load(const LoaderParams* params);

	//getters for collision detection
	Vector2D& getPosition() { return _position; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }
protected:
	string _textureID;
	int _currentFrame, _currentRow;
	int _numFrames;
	int _width, _height;

	Vector2D _position;
	Vector2D _velocity;
	Vector2D _acceleration;
};

