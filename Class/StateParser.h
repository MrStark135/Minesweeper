#pragma once
#include "GameObject.h"
#include "TinyXML/tinyxml.h"
#include <vector>
#include <string>
using namespace std;

class StateParser
{
public:
	bool ParseState(const char* stateFile, string stateID, vector<GameObject*>* objects, vector<string>* textureIDs);
	void parseParams(const char* fileName, int& width, int& height, int& numMines, int& offsetX, int& offsetY);
private:
	void ParseObjects(TiXmlElement* stateRoot, vector<GameObject*>* objects);
	void ParseTextures(TiXmlElement* stateRoot, vector<string>* textureIDs);
};

