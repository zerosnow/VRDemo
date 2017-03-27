#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LyricContent {
	int time;
	string lyric;
};

class LyricUtil
{
public:
	LyricUtil();
	~LyricUtil();

	bool loadFile(string fileName);
	bool loadFileFromAsset(string fileName);
	int getCurrentPosition(int currTime, int preI);
	string getLyricString(int position);
private:
	void insertToList(string *tempTemp, int p, string str);
	vector<struct LyricContent> lrcList;
};

