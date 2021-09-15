#pragma once
#include <string>
using namespace std;

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, int numFrames, string textureID, int callbackID = 0, int animSpeed = 0)
		:_x(x), _y(y), _width(width), _height(height), _numFrames(numFrames), _textureID(textureID), _callbackID(callbackID), _animSpeed(animSpeed)
	{};
	int getX() const { return _x; }
	int getY() const { return _y; }
	int getWidth() const { return _width; }
	int getHeight() const { return _height; }
	int getFrames() const { return _numFrames; }
	int getCallbackID() const { return _callbackID; }
	int getAnimSpeed() const { return _animSpeed; }
	string GetTextureID() const { return _textureID; }
private:
	int _x, _y;
	int _width, _height;
	int _numFrames;
	string _textureID;
	//for MenuButton and AnimatedGraphic
	int _callbackID;
	int _animSpeed;
};