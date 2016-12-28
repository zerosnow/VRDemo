#include "VRScene.h"
#include "LyricLayer.h"
#include "logutil.h"
#include <stdio.h>
#include <pthread.h>
#include "audio/AudioHelper.h"



bool VRScene::init()
{
	if (!Scene::init())
	{
		return false;
	}


	auto glview = Director::getInstance()->getOpenGLView();
    auto vrimpl = glview->getVR();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	sprite = Sprite3D::create("boss.c3b");
	sprite->setScale(5.f);
	sprite->setPosition3D(Vec3(0, 0, 500));
	
	addChild(sprite, 1);

	auto _textureCube = TextureCube::create("skybox/left.jpg", "skybox/right.jpg",
        "skybox/top.jpg", "skybox/bottom.jpg",
        "skybox/front.jpg", "skybox/back.jpg");

    _textureCube->retain();

    //set texture parameters
    Texture2D::TexParams tRepeatParams;
    tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
    tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;
    _textureCube->setTexParameters(tRepeatParams);

	

    auto shader = GLProgram::createWithFilenames("cube_map.vert","cube_map.frag");
	auto _state = GLProgramState::create(shader);
    // pass the texture sampler to our custom shader
    _state->setUniformTexture("u_cubeTex", _textureCube);

    // config skybox
    auto _skyBox = Skybox::create();
    _skyBox->retain();

    _skyBox->setTexture(_textureCube);
    addChild(_skyBox);

    lyricLayer = LyricLayer::create();
    lyricLayer->setPosition3D(Vec3(0.0f, 0.0f, -100.0f));

	getDefaultCamera()->addChild(lyricLayer);

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
	currentTime += delta;
	if (currentTime >= 2 && currentTime-delta < 2)
	{
		AudioHelper::getInstance()->startPlayAssert("song.wav");
		AudioHelper::getInstance()->startRecord(FileUtils::getInstance()->getWritablePath() += "audio.pcm");

	}
	if (currentTime >= 30 && currentTime - delta < 30)
	{
		AudioHelper::getInstance()->stopPlay();
		AudioHelper::getInstance()->stopRecord();
		AudioHelper::getInstance()->startPlay(FileUtils::getInstance()->getWritablePath() += "audio.pcm");
	}
	
	
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


