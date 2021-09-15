#pragma once
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic :public SDLGameObject
{
public:
	AnimatedGraphic();

	virtual void Update();
	virtual void Draw();
	virtual void Clean();

	virtual void Load(const LoaderParams* params);
private:
	int _animSpeed;
};

class AnimatedGraphicCreator :public BaseCreator
{
public:
	GameObject* createGameObject() const
	{
		return new AnimatedGraphic();
	}
};