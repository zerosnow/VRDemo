#include "VRScene.h"
#include <stdio.h>
#include <pthread.h>
#include "audio/AudioHelper.h"
#include "utils/logutil.h"
#include "gvr-sdk/CCVRGvrRenderer.h"

void VRScene::onLeftDown()
{
	LOGD("onLeftDown");
	AudioHelper::getInstance()->playBack();
	AudioHelper::getInstance()->playPause();
}

void VRScene::onRightDown()
{
	LOGD("onRightDown");
	AudioHelper::getInstance()->playForward();
	AudioHelper::getInstance()->playPause();
}

void VRScene::onAppButtonUp()
{
	LOGD("onAppButtonUp");
	AudioHelper::getInstance()->changePlayState();
}

void VRScene::updateOrientation(gvr_quatf orientation)
{
	Quaternion quat(orientation.qx, orientation.qy, orientation.qz, orientation.qw);
	sprite->setRotationQuat(quat);
}

void VRScene::onTouchUp()
{
	LOGD("onTouchUp");
	AudioHelper::getInstance()->playResume();
}

bool VRScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto glview = Director::getInstance()->getOpenGLView();
    auto vrimpl = glview->getVR();
    dayDreamController = new DayDreamController(dynamic_cast<VRGvrRenderer *>(vrimpl)->getController(), this);
	renderHelper = new RenderHelper(this);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	sprite = Sprite3D::create("boss.c3b");
	sprite->setScale(5.f);
	sprite->setPosition3D(Vec3(0, 0, 500));
	
	addChild(sprite, 1);

	getDefaultCamera()->setPosition3D(Vec3(0, 0, 0));

    /*if (JniHelper::getStaticMethodInfo(methodInfo, "org.cocos2dx.cpp.MediaPlayerHelper", 
        "playMusic", "(Ljava/lang/String;)V")) {
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, 
            methodInfo.env->NewStringUTF("song.wav"));
    } else {
        LOGD("getStaticMethodInfo error");
    }*/

    scheduleUpdate();

	return true;
}

float currentTime = 0;

void VRScene::update(float delta) 
{
	dayDreamController->onUpdate();
	currentTime += delta;

	if (currentTime >= 2 && currentTime-delta < 2)
	{
		AudioHelper::getInstance()->startPlayAssert("song.wav");
		// AudioHelper::getInstance()->startRecord(FileUtils::getInstance()->getWritablePath() += "audio.pcm");
	}

	if (currentTime >= 5 && currentTime-delta < 5)
	{
		renderHelper->setSkybox(DARK_STORMY);
	}
	if (currentTime >= 10 && currentTime-delta < 10)
	{
		renderHelper->setSkybox(SNOW_MOUNTAIN);
	}
	if (currentTime >= 15 && currentTime-delta < 15)
	{
		renderHelper->setSkybox(SUN_SET);
	}


	// if (currentTime >= 30 && currentTime - delta < 30)
	// {
	// 	AudioHelper::getInstance()->stopPlay();
	// 	AudioHelper::getInstance()->stopRecord();
	// 	AudioHelper::getInstance()->startPlay(FileUtils::getInstance()->getWritablePath() += "audio.pcm");
	// }
	
	
//	LOGD("getTime : %lf", getTime());

	

 //   if (JniHelper::getStaticMethodInfo(methodInfo, "org.cocos2dx.cpp.MediaPlayerHelper", 
 //       "getCurrentPositon", "()I")) {
 //       int currentPosition = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, 
 //           methodInfo.env->NewStringUTF("song.wav"));
 //       LOGD("current position = %d", currentPosition);
 //   } else {
 //       LOGD("getStaticMethodInfo error");
 //   }
	///*LOGD("camera: %f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", mat.m[0], mat.m[1], mat.m[2], mat.m[3],
	//	mat.m[4], mat.m[5], mat.m[6], mat.m[7], mat.m[8], mat.m[9], mat.m[10], mat.m[11], mat.m[12], mat.m[13], mat.m[14], mat.m[15]);*/

}


