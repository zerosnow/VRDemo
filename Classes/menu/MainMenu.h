#pragma once

#include "cocos2d.h"
#include "VRMenuItem.h"
#include <vector>

using namespace cocos2d;

enum menuOperation {
	APPEAR,
	DISAPPEAR,
	LEFT_SLIDE,
	RIGHT_SLIDE,
	UP_SLIDE,
	DOWN_SLIDE
};

class MainMenu
{
public:
	MainMenu(Scene *scene);
	~MainMenu();

	void popUp();
	void close();

	void leftSlide();
	void rightSlide();

	void confirm();

private:
	void updateMenu(vector<VRMenuItem *> list, enum menuOperation op);

	vector<VRMenuItem *> mainMenuList;
	vector<VRMenuItem *> subMenuList;

	int currentPosition;
	Scene *currentScene;
};