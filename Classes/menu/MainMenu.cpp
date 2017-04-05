#include "MainMenu.h"

extern string mainMenuData[][2];
extern string lyricMenuData[][2];
extern string bgMenuData[][2];
extern string weatherData[][2];

MainMenu::MainMenu(Scene *scene)
{
	currentScene = scene;
	for (int i = 0; i < 4; ++i)
	{	
		auto item = new VRMenuItem(mainMenuData[i][0], mainMenuData[i][1]);
		//初始化
		item->setScale(0.f);
		item->setPosition3D(Vec3(0.f, 0.f, -150.f));
		currentScene->getDefaultCamera()->addChild(item);
		mainMenuList.push_back(item);
	}
	currentPosition = 1;
}

MainMenu::~MainMenu()
{

}

void MainMenu::popUp()
{
	updateMenu(mainMenuList, APPEAR);
}

void MainMenu::close()
{
	updateMenu(mainMenuList, DISAPPEAR);
}

void MainMenu::leftSlide()
{
	if (currentPosition == 0)
	{
		return;
	}
	currentPosition--;
	updateMenu(mainMenuList, LEFT_SLIDE);
}

void MainMenu::rightSlide()
{
	if (currentPosition == 3)
	{
		return;
	}
	currentPosition++;
	updateMenu(mainMenuList, RIGHT_SLIDE);
}

void MainMenu::confirm()
{

}

void MainMenu::updateMenu(vector<VRMenuItem *> list, enum menuOperation op)
{
	switch(op)
	{
		case APPEAR:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = Spawn::create(MoveTo::create(0.8f, Vec3(100.0*(i-currentPosition), 0, -150.0)), ScaleTo::create(0.8f, 1.0f), nullptr);
				list.at(i)->runAction(action);
			}
			break;
		}
		case DISAPPEAR:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = Spawn::create(MoveTo::create(0.8f, Vec3(0.f, 0.f, -150.0)), ScaleTo::create(0.8f, 0.01f), nullptr);
				list.at(i)->runAction(action);
			}
			break;
		}
		case LEFT_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveTo::create(0.8f, Vec3(100.0*(i-currentPosition), 0, -150.0));
				list.at(i)->runAction(action);
			}
			break;
		}
		case RIGHT_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveTo::create(0.8f, Vec3(100.0*(i-currentPosition), 0, -150.0));
				list.at(i)->runAction(action);
			}
			break;
		}
		case UP_SLIDE:
		{	
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveBy::create(0.8f, Vec3(0.f, 60.f, 0.f));
				list.at(i)->runAction(action);
			}
			break;
		}
		case DOWN_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveBy::create(0.8f, Vec3(0.f, -60.f, 0.f));
				list.at(i)->runAction(action);
			}
			break;
		}
	}
}
