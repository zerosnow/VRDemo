#pragma once

#include "cocos2d.h"
#include "LyricLayer.h"

using namespace cocos2d;

class VRScene:public cocos2d::Scene
{
public:
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(VRScene);

private:
	LyricLayer *lyricLayer;
	Sprite3D *sprite;
    JniMethodInfo methodInfo;
};

