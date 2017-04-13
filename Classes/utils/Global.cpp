#include "Global.h"

Global::Global() 
{
}

Global *Global::instance = nullptr;
Global *Global::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Global();
	}
	return instance;
}


void Global::setCurrentScene(Scene *scene)
{
	getInstance()->currentScene = scene;
}

Scene *Global::getCurrentScene()
{
	return getInstance()->currentScene;
}

struct SongInfo *Global::songInfo = nullptr;
SongInfo *Global::getSongInfo()
{
	if (songInfo == nullptr)
	{
		songInfo = new SongInfo;
		JNIEnv *env = JniHelper::getEnv();
		jclass cls = env->FindClass("org/cocos2dx/cpp/VRSongInfo");
		jfieldID songFileNameId = env->GetStaticFieldID(cls, "songFileName", "Ljava/lang/String;");
		jfieldID lyricFileNameId = env->GetStaticFieldID(cls, "lyricFileName", "Ljava/lang/String;");
		jfieldID weatherTypeId = env->GetStaticFieldID(cls, "weatherType", "I");
		jfieldID bgTypeId = env->GetStaticFieldID(cls, "bgType", "I");
		jfieldID playTypeId = env->GetStaticFieldID(cls, "playType", "I");

		jstring jSongFileName = (jstring)env->GetStaticObjectField(cls, songFileNameId);
		jstring jLyricFileName = (jstring)env->GetStaticObjectField(cls, lyricFileNameId);
		songInfo->songFileName = JniHelper::jstring2string(jSongFileName);
		songInfo->lyricFileName = JniHelper::jstring2string(jLyricFileName);
		songInfo->weatherType = env->GetStaticIntField(cls, weatherTypeId);
		songInfo->bgType = env->GetStaticIntField(cls, bgTypeId);
		songInfo->playType = env->GetStaticIntField(cls, playTypeId);
	}
	return songInfo;
}

bool Global::isRecord()
{
	return getSongInfo()->playType == 2;
}

string Global::getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	struct tm *tm = localtime(&tv.tv_sec);

	char currentTime[128];
	strftime(currentTime, 128, "%F %T", tm);
	string time(currentTime);
	return time;
}