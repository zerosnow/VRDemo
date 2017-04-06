#pragma once

#include "cocos2d.h"
using namespace cocos2d;

class Global
{
public:
	static Global *getInstance();
	static void setCurrentScene(Scene *scene);
	static Scene *getCurrentScene();
private:
	Global();
	static Global *instance;
	Scene *currentScene;
};