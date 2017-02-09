#include "LyricUtil.h"
#include "cocos2d.h"
#include "../logutil.h"
#include <fstream>
#include <regex>

using namespace cocos2d;


LyricUtil::LyricUtil()
{
}

LyricUtil::~LyricUtil()
{
}

bool LyricUtil::loadFile(string fileName)
{
	ifstream file(fileName.c_str());

	string buffer;

	if (!file.is_open())
	{
		LOGD("%s open fail", fileName.c_str());
	}

	while (!file.eof()) 
	{
		getline(file, buffer);
		while ()


	}
}

bool LyricUtil::loadFileFromAsset(string fileName)
{
	string fullFileName = FileUtils::getInstance()->fullPathForFilename(fileName);

	Data data = FileUtils::getInstance()->getDataFromFile(fullFileName);

	std::string destPath = FileUtils::getInstance()->getWritablePath();
	destPath += fileName;
	FILE *fp = fopen(destPath.c_str(), "w+");
	fwrite(data.getBytes(), sizeof(char), data.getSize(), fp);
	fclose(fp);
	data.clear();

	loadFile(destPath);
}

int LyricUtil::getCurrentPosition(long currTime)
{

}