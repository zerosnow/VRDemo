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

enum MenuState {
	MENU_OFF,
	MENU_ON
};

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

	enum MenuState getMenuState();
private:
	void updateMenu(vector<VRMenuItem *> list, enum menuOperation op, int position);
	void initSubMenuData(string subMenuData[][2], int dataNum);

	vector<VRMenuItem *> mainMenuList;
	vector<VRMenuItem *> subMenuList;

	int mainPosition;
	int subPosition;
    enum MenuState state = MENU_OFF;
};