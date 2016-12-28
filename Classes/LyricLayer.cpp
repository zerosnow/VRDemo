#include "LyricLayer.h"

USING_NS_CC;

bool LyricLayer::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::create();
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    auto sprite = Sprite::create("HelloWorld.png");
    this->addChild(sprite, 1);

    label->setString("111111111111\n11111111");
    this->addChild(label, 1);

    return true;
}