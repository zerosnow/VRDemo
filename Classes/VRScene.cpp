#include "VRScene.h"
#include <stdio.h>
#include <pthread.h>
#include "audio/AudioHelper.h"
#include "utils/logutil.h"
#include "gvr-sdk/CCVRGvrRenderer.h"
#include "utils/Global.h"

string getCurrentTime();
bool checkStart();

void VRScene::onLeftDown()
{
	LOGD("onLeftDown");
	if (mainMenu->getMenuState() == MENU_OFF)
	{
		AudioHelper::getInstance()->playPause();
		AudioHelper::getInstance()->playBack();
	}
}

void VRScene::onRightDown()
{
	LOGD("onRightDown");
	if (mainMenu->getMenuState() == MENU_OFF)
	{
		AudioHelper::getInstance()->playPause();
		AudioHelper::getInstance()->playForward();
	}
}

void VRScene::onLeftUp()
{
	LOGD("onLeftUp");
	if(mainMenu->getMenuState() == MENU_ON)
	{
		mainMenu->leftSlide();
	}
}

void VRScene::onRightUp()
{
	LOGD("onRightUp");
	if(mainMenu->getMenuState() == MENU_ON)
	{
		mainMenu->rightSlide();
	}
}

void VRScene::onAppButtonUp()
{
	LOGD("onAppButtonUp");
	if (checkStart())
	{
		return ;
	}
	if (mainMenu->getMenuState() == MENU_OFF)
	{
		AudioHelper::getInstance()->playPause();
		AudioHelper::getInstance()->recordPause();
		mainMenu->popUp();
	} else if(mainMenu->getMenuState() == MENU_ON)
	{
		mainMenu->confirm();
		if (mainMenu->getMenuState() == MENU_OFF)
		{
			AudioHelper::getInstance()->playResume();
		}
	}
}

void VRScene::updateOrientation(gvr_quatf orientation)
{
	// Quaternion quat(orientation.qx, orientation.qy, orientation.qz, orientation.qw);
	// sprite->setRotationQuat(quat);
}

void VRScene::onTouchUp()
{
	LOGD("onTouchUp");
	if (checkStart())
	{
		return ;
	}
	if (mainMenu->getMenuState() == MENU_OFF)
	{
		AudioHelper::getInstance()->playResume();
	}
}

void dealSongInfo()
{
	SongInfo *songInfo = Global::getInstance()->getSongInfo();
	switch(songInfo->weatherType)
	{
		case 0:
		RenderHelper::getInstance()->setWeather(WEATHER_SNOW);
		break;
		case 1:
		RenderHelper::getInstance()->setWeather(WEATHER_RAIN);
		break;
		default:
		break;
	}
	switch(songInfo->bgType)
	{
		case 0:
		RenderHelper::getInstance()->setSkybox(CLOUDY_LIGHT_RAYS);
		break;
		case 1:
		RenderHelper::getInstance()->setSkybox(DARK_STORMY);
		break;
		case 2:
		RenderHelper::getInstance()->setSkybox(SNOW_MOUNTAIN);
		break;
		case 3:
		RenderHelper::getInstance()->setSkybox(SUN_SET);
		break;
		default:
		break;
	}
}

bool VRScene::init()
{
	LOGD("VRScene::init");
	if (!Scene::init())
	{
		return false;
	}

	auto glview = Director::getInstance()->getOpenGLView();
    auto vrimpl = glview->getVR();
    Global::setCurrentScene(this);
    dayDreamController = new DayDreamController(dynamic_cast<VRGvrRenderer *>(vrimpl)->getController(), this);
    RenderHelper::getInstance()->init();
	mainMenu = new MainMenu();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto sprite = Sprite3D::create("boss.c3b");

	getDefaultCamera()->setPosition3D(Vec3(0, 0, 0));

    dealSongInfo();

    scheduleUpdate();

	return true;
}


float currentTime = 0;

void VRScene::update(float delta) 
{
	dayDreamController->onUpdate();
	currentTime += delta;

	if (currentTime >= 5 && currentTime-delta < 5)
	{
		onAppButtonUp();
	}

	if (currentTime >= 10 && currentTime-delta < 10)
	{
		AudioHelper::getInstance()->stopPlay();
		AudioHelper::getInstance()->stopRecord();
	}
}

bool checkStart()
{
	if (RenderHelper::getInstance()->isStart())
	{
		RenderHelper::getInstance()->closeStartLayer();
		AudioHelper::getInstance()->startPlayAssert(Global::getInstance()->getSongInfo()->songFileName);

		if (Global::getInstance()->isRecord())
		{
			string songFileName = Global::getInstance()->getSongInfo()->songFileName;
			AudioHelper::getInstance()->startRecord(FileUtils::getInstance()->getWritablePath() + 
				songFileName.substr(0, songFileName.find_last_of(".")) + "_" + Global::getCurrentTime() + ".pcm");
		}
		return true;
	}
	return false;
}


