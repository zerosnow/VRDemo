#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LyricContent {
	long time;
	string lyric;
};

class LyricUtil
{
public:
	LyricUtil();
	~LyricUtil();

	bool loadFile(string fileName);
	bool loadFileFromAsset(string fileName);
	int getCurrentPosition(long currTime);

private:
	vector<struct LyricContent> lrcList;
};

