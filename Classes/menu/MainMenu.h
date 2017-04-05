#pragma once

#include "cocos2d.h"
#include "VRMenuItem.h"
#include <vector>

using namespace cocos2d;

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void popUp();
	void close();

	void leftSlide();
	void rightSlide();

	void confirm();

private:
	vector<VRMenuItem *> mainMenuList;
	vector<VRMenuItem *> subMenuList;
};