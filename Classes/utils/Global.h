#pragma once

#include "SongInfo.h"
#include "cocos2d.h"
using namespace cocos2d;

class Global
{
public:
	static Global *getInstance();
	static void setCurrentScene(Scene *scene);
	static Scene *getCurrentScene();
	static SongInfo *getSongInfo();
private:
	Global();
	static Global *instance;
	Scene *currentScene;
	static struct SongInfo *songInfo;
};