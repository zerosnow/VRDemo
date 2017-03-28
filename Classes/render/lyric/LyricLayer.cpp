#include "LyricLayer.h"
#include "audio/AudioHelper.h"
#include "utils/logutil.h"

bool LyricLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    for (int i = 0; i < 4; ++i)
    {
        label[i] = Label::create();
        if (i == 1)
        {
            Color4B textColor(255, 0, 0, 255);
            label[i]->setTextColor(textColor);
        }
        label[i]->setScale(0.8);
        label[i]->setPosition(Vec2(0,
                               50 - i * (label[i]->getContentSize().height + 20)));
        this->addChild(label[i], 1);
    }
    

    lyricUtil = new LyricUtil;
    lyricUtil->loadFileFromAsset("埋葬冬天.lrc");

    scheduleUpdate();

    return true;
}

void LyricLayer::update(float delta)
{
    static int i = 0, preI = 0;
    const static int offset = 100;
    i = lyricUtil->getCurrentPosition((int)(AudioHelper::getInstance()->getPlayTime() * 1000000 - offset), preI);
    if (preI != i || i == 0)
    {
        preI = i;
        for (int j = 0; j < 4; ++j)
        {
            label[j]->setString(lyricUtil->getLyricString(i + j - 1));
        }
    }
}