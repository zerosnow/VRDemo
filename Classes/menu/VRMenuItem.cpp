#include "VRMenuItem.h"

VRMenuItem::VRMenuItem(string text, string bgFile)
{
	if (!Layer::init())
	{
		return;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto bg = Sprite::create(bgFile);
    bg->setPosition(Vec2(0, 20));
    this->addChild(bg);

    auto label = Label::create();
    label->setString(text);
    this->addChild(label);
}

VRMenuItem::~VRMenuItem()
{

}