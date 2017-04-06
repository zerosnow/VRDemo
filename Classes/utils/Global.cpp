#include "Global.h"

Global::Global() 
{
}

Global *Global::instance = nullptr;
Global *Global::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}
	return instance;
}


void Global::setCurrentScene(Scene *scene)
{
	getInstance()->currentScene = scene;
}

Scene *Global::getCurrentScene()
{
	return getInstance()->currentScene;
}

