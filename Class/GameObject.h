#pragma once
#include "LoaderParams.h"

class GameObject
{
public:
	//any gameObject inherited type will define these funcs()
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Clean() = 0;

	//to load params
	virtual void Load(const LoaderParams* params) = 0;
protected:
	GameObject() {};
	virtual ~GameObject() {};
};

