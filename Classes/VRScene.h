#pragma once

#include "cocos2d.h"
#include "render/RenderHelper.h"
#include "menu/MainMenu.h"
#include "controller/DayDreamController.h"
#include "controller/ControllerInterface.h"


using namespace cocos2d;

class VRScene:public cocos2d::Scene, public ControllerInterface
{
public:
	virtual bool init();
	virtual void update(float delta);
	virtual void onLeftDown();
	virtual void onRightDown();
	virtual void onLeftUp();
	virtual void onRightUp();
	virtual void onAppButtonUp();
	virtual void updateOrientation(gvr_quatf orientation);
	virtual void onTouchUp();

	CREATE_FUNC(VRScene);

private:
	MainMenu *mainMenu;
    JniMethodInfo methodInfo;
    DayDreamController *dayDreamController;
};

