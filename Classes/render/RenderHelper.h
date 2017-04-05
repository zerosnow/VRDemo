#pragma once

#include "cocos2d.h"
#include "lyric/LyricLayer.h"
#include "background/SkyboxHelper.h"
#include "weather/WeatherHelper.h"

using namespace cocos2d;

class RenderHelper
{
public:
	RenderHelper(Scene *scene);
	~RenderHelper();

	void setSkybox(enum SkyboxType type);
	void setWeather(enum WeatherType type);
	bool init();

private:
	LyricLayer *lyricLayer;
	SkyboxHelper *skyboxHelper;
	WeatherHelper *weatherHelper;
	Scene *currentScene;
};