#pragma once

#include "cocos2d.h"
#include "lyric/LyricLayer.h"
#include "background/SkyboxHelper.h"
#include "weather/WeatherHelper.h"

using namespace cocos2d;

class RenderHelper
{
public:
	static RenderHelper *getInstance();
	~RenderHelper();

	void setSkybox(enum SkyboxType type);
	void setWeather(enum WeatherType type);
	void setLyricLayer(bool visible);
	void closeStartLayer();
	bool isStart();
	bool init();

private:
	RenderHelper();
	void initStartLayer();
	static RenderHelper *instance;

	LyricLayer *lyricLayer;
	SkyboxHelper *skyboxHelper;
	WeatherHelper *weatherHelper;
	Layer *startLayer;
};