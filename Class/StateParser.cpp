#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "StateParser.h"
#include <iostream>

GameObjectFactory* GameObjectFactory::_instance;

bool StateParser::ParseState(const char* stateFile, string stateID, vector<GameObject*>* objects, vector<string>* textureIDs)
{
	//create XML document
	TiXmlDocument xmlDoc;
	//load the state file
	if (!xmlDoc.LoadFile(stateFile))
	{
		cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}
	//get root element
	TiXmlElement* root = xmlDoc.RootElement();
	//declare state root
	TiXmlElement* stateRoot = 0;
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (string(e->Value()) == stateID)
		{
			stateRoot = e;
		}
	}
	//declare textures root
	TiXmlElement* textureRoot = 0;
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("textures"))
		{
			textureRoot = e;
		}
	}
	ParseTextures(textureRoot, textureIDs);
	//declare objects root
	TiXmlElement* objectsRoot = 0;
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (e->Value() == string("objects"))
		{
			objectsRoot = e;
		}
	}
	ParseObjects(objectsRoot, objects);
	return true;
}

void StateParser::ParseTextures(TiXmlElement* stateRoot, vector<string>* textureIDs)
{
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		const char* filename = e->Attribute("filename");
		string textureID = e->Attribute("textureID");
		textureIDs->push_back(textureID);
		TextureManager::Instance()->LoadPNG(filename, textureID, Game::Instance()->GetRenderer());
	}

}
void StateParser::ParseObjects(TiXmlElement* stateRoot, vector<GameObject*>* objects)
{
	for (TiXmlElement* e = stateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		string textureID;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("animSpeed", &animSpeed);
		e->Attribute("callbackID", &callbackID);
		textureID = e->Attribute("textureID");
		GameObject* gameObject = GameObjectFactory::Instance()->Create(string(e->Attribute("type")));
		gameObject->Load(new LoaderParams(x, y, width, height, numFrames, textureID, callbackID, animSpeed));
		objects->push_back(gameObject);
	}
}
void StateParser::parseParams(const char* fileName, int& width, int& height, int& numMines, int& offsetX, int& offsetY)
{
	//create XML document
	TiXmlDocument xmlDoc;
	//load the file
	if (!xmlDoc.LoadFile(fileName))
	{
		cerr << xmlDoc.ErrorDesc() << "\n";
		return;
	}
	//get root element
	TiXmlElement* root = xmlDoc.RootElement();
	//declare state root
	TiXmlElement* playStateRoot = 0;
	for (TiXmlElement* e = root->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (string(e->Value()) == string("play"))
		{
			playStateRoot = e;
		}
	}
	for (TiXmlElement* e = playStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		if (string(e->Value()) == string("params"))
		{
			e->Attribute("width", &width);
			e->Attribute("height", &height);
			e->Attribute("numMines", &numMines);
			e->Attribute("offsetX", &offsetX);
			e->Attribute("offsetY", &offsetY);
		}
	}
}