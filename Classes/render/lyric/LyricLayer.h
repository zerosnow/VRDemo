#pragma once

#include "cocos2d.h"
#include "utils/LyricUtil.h"

USING_NS_CC;

class LyricLayer : public cocos2d::Layer
{
public:
	
	virtual bool init();
	virtual void update(float delta);

	CREATE_FUNC(LyricLayer);

private:
    LyricUtil *lyricUtil;
    Label *label[4];
};