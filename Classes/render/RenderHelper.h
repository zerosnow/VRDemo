#pragma once

#include "cocos2d.h"
#include "lyric/LyricLayer.h"
#include "background/SkyboxHelper.h"

using namespace cocos2d;

class RenderHelper
{
public:
	RenderHelper(Scene *scene);
	~RenderHelper();

	bool init();

private:
	LyricLayer *lyricLayer;
	SkyboxHelper *skyboxHelper;
	Scene *currentScene;
};