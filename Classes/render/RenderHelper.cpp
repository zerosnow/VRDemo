#include "RenderHelper.h"
#include "utils/Global.h"

RenderHelper *RenderHelper::instance = nullptr;
RenderHelper *RenderHelper::getInstance()
{
	if (instance == nullptr)
	{
		instance = new RenderHelper;
	}
	return instance;
}


RenderHelper::RenderHelper()
{
	
}

bool RenderHelper::init()
{
	lyricLayer = LyricLayer::create();
    lyricLayer->setPosition3D(Vec3(0.0f, 0.0f, -100.0f));

	Global::getCurrentScene()->getDefaultCamera()->addChild(lyricLayer);

	skyboxHelper = new SkyboxHelper();
	skyboxHelper->setSkybox(SNOW_MOUNTAIN);
	auto skybox = skyboxHelper->getSkybox();
	Global::getCurrentScene()->addChild(skybox);

	weatherHelper = new WeatherHelper();
	return true;
}

RenderHelper::~RenderHelper()
{
	delete lyricLayer;
}

void RenderHelper::setSkybox(enum SkyboxType type)
{
	skyboxHelper->setSkybox(type);
}

void RenderHelper::setWeather(enum WeatherType type)
{
	weatherHelper->setWeather(type);
}

void RenderHelper::setLyricLayer(bool visible)
{
	lyricLayer->setVisible(visible);
}


