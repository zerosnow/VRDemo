#include "RenderHelper.h"
#include "utils/Global.h"
#include "utils/logutil.h"

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
	LOGD("RenderHelper::init()");
	lyricLayer = LyricLayer::create();
    lyricLayer->setPosition3D(Vec3(0.0f, 0.0f, -100.0f));

	Global::getCurrentScene()->getDefaultCamera()->addChild(lyricLayer);

	skyboxHelper = new SkyboxHelper();
	skyboxHelper->setSkybox(SNOW_MOUNTAIN);
	auto skybox = skyboxHelper->getSkybox();
	Global::getCurrentScene()->addChild(skybox);
	weatherHelper = new WeatherHelper();

	initStartLayer();
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

void RenderHelper::closeStartLayer()
{
	Global::getCurrentScene()->getDefaultCamera()->removeChild(startLayer);
	startLayer = nullptr;
}

bool RenderHelper::isStart()
{
	return startLayer != nullptr;
}

void RenderHelper::initStartLayer()
{
	string bgFile("blackbackground.jpg");
	string text("按任意键开始");
	if (Global::getInstance()->isRecord())
	{
		text += "录制";
	} else {
		text += "播放";
	}
	startLayer = Layer::create();
	auto bg = Sprite::create(bgFile);
    startLayer->addChild(bg);

    auto label = Label::create();
    label->setString(text); 
    startLayer->addChild(label);

	startLayer->setPosition3D(Vec3(0.f, 0.f, -150.f));
	Global::getCurrentScene()->getDefaultCamera()->addChild(startLayer);
}

enum WeatherType RenderHelper::getWeatherType()
{
	return weatherHelper->getWeatherType();
}

enum SkyboxType RenderHelper::getSkyboxType()
{
	return skyboxHelper->getSkyboxType();
}