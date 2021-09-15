#pragma once

#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class Background :public SDLGameObject
{
public:
	Background();

	virtual void Update();
	virtual void Draw();
	virtual void Clean();

	virtual void Load(const LoaderParams* params);
};

class BackgroundCreator :public BaseCreator
{
public:
	GameObject* createGameObject() const
	{
		return new Background();
	}
};

