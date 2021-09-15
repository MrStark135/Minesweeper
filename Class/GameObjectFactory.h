#pragma once
#include "GameObject.h"

#include <string>
#include <map>
#include <iostream>
using namespace std;

//for each type there will be a creator
class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() { ; }
};

class GameObjectFactory
{
public:
	//to register a new type or create an object of a registered type
	bool RegisterType(string typeID, BaseCreator* creator)
	{
		map<string, BaseCreator*>::iterator it = _creators.find(typeID);
		/*if (it != _creators.end())
		{
			delete creator;
			return false;
		}*/
		_creators[typeID] = creator;
		return true;
	}
	GameObject* Create(string typeID)
	{
		map<string, BaseCreator*>::iterator it = _creators.find(typeID);
		if (it == _creators.end())
		{
			cout << "Could not find type: " << typeID << endl;
			return nullptr;
		}
		BaseCreator* creator = it->second;
		return creator->createGameObject();
	}

	//to make it a singleton
	static GameObjectFactory* Instance()
	{
		if (_instance == nullptr)
		{
			_instance = new GameObjectFactory();
		}
		return _instance;
	}
private:
	map<string, BaseCreator*> _creators;
	//singleton
	static GameObjectFactory* _instance;
	GameObjectFactory() {};
};
