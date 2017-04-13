#pragma once

#include <iostream>
#include "SongInfo.h"
#include "cocos2d.h"
using namespace cocos2d;
using namespace std;

class Global
{
public:
	static Global *getInstance();
	static void setCurrentScene(Scene *scene);
	static Scene *getCurrentScene();
	static SongInfo *getSongInfo();
	static bool isRecord();
	static string getCurrentTime();
private:
	Global();
	static Global *instance;
	Scene *currentScene;
	static struct SongInfo *songInfo;
};