#include "RenderHelper.h"

RenderHelper::RenderHelper(Scene *scene)
{
	currentScene = scene;

	lyricLayer = LyricLayer::create();
    lyricLayer->setPosition3D(Vec3(0.0f, 0.0f, -100.0f));

	currentScene->getDefaultCamera()->addChild(lyricLayer);

	skyboxHelper = new SkyboxHelper();
	skyboxHelper->setSkybox(SNOW_MOUNTAIN);
	auto skybox = skyboxHelper->getSkybox();
	currentScene->addChild(skybox);
}

bool RenderHelper::init()
{
	return true;
}

RenderHelper::~RenderHelper()
{
	delete lyricLayer;
}

