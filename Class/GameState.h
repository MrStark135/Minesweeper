#pragma once
#include <string>
#include <vector>
using namespace std;

class GameState
{
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual bool onEnter() = 0;
	virtual bool onExit() = 0;

	virtual std::string getStateID() const = 0;
protected:
	vector<string> _textureIDlist;

//menu button functionalities
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector<Callback>& callbacks) = 0;
	std::vector<Callback> _callbacks;
};

