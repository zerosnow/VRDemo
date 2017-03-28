#include "LyricUtil.h"
#include "cocos2d.h"
#include "utils/logutil.h"
#include <fstream>
#include <regex>

using namespace cocos2d;

const static int MAX_LYRIC_REPEAT_NUM = 3;
regex rules("(\\[[0-9]{1,2}.[0-9]{1,2}.[0-9]{1,2}\\])");

LyricUtil::LyricUtil()
{
}

LyricUtil::~LyricUtil()
{
}

void LyricUtil::insertToList(string *tempTemp, int p, string str) {
	int min, sec, ms;
	for (int i=0; i<p; i++) 
	{
		sscanf(tempTemp[i].c_str(), "[%d%*c%d%*c%d]", &min, &sec, &ms);
		if (min < 0 || sec < 0 || sec > 60 || ms < 0 || ms > 1000) 
		{
			LOGE("timeTemp error!");
		}
		LyricContent content;
		content.time = min * 60 * 1000 + sec * 1000 + ms;
		content.lyric = str;
		lrcList.push_back(content);
	}
}

bool lyricSort(const struct LyricContent &v1, const struct LyricContent &v2)
{
	return v1.time < v2.time;
}

bool LyricUtil::loadFile(string fileName)
{
	ifstream file(fileName.c_str());

	if (!file.is_open())
	{
		LOGD("%s open fail", fileName.c_str());
		return false;
	}

	string buffer;

	while (file)
	{
		getline(file, buffer);
		if (buffer != "")
		{
			smatch sm;
			string timeTemp[MAX_LYRIC_REPEAT_NUM];
			int p = 0;
			while (regex_search(buffer, sm, rules)) {
				timeTemp[p++] = sm[0];
				buffer = sm.suffix().str();
			}
			insertToList(timeTemp, p, buffer);
		}
	}
	sort(lrcList.begin(), lrcList.end(), lyricSort);
	return true;
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

	return loadFile(destPath);
}

int LyricUtil::getCurrentPosition(int currTime, int preI)
{
	if (currTime <= 0) {
		 return 0;
	}
	if (currTime < lrcList.at(preI).time)
	{
		preI = 0;
	}
	for (int i = preI; i < lrcList.size(); ++i)
	{
		if (currTime < lrcList.at(i).time) {
			return i-1;
		}
	}
	return lrcList.size();
}

string LyricUtil::getLyricString(int position)
{
	if (position < 0 || position >= lrcList.size())
	{
		return "";
	}
	return lrcList.at(position).lyric;
}
