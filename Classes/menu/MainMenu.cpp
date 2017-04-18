#include "MainMenu.h"
#include "utils/Global.h"
#include "render/RenderHelper.h"
#include "audio/AudioHelper.h"

extern string mainMenuData[][2];
extern string lyricMenuData[][2];
extern string bgMenuData[][2];
extern string weatherMenuData[][2];

MainMenu::MainMenu()
{
	for (int i = 0; i < 4; ++i)
	{	
		auto item = new VRMenuItem(mainMenuData[i][0], mainMenuData[i][1]);
		//初始化
		item->setScale(0.f);
		item->setPosition3D(Vec3(0.f, 0.f, -150.f));
		Global::getCurrentScene()->getDefaultCamera()->addChild(item);
		mainMenuList.push_back(item);
	}
	mainPosition = 1;
	subPosition = -1;
}

MainMenu::~MainMenu()
{

}

void MainMenu::popUp()
{
	//弹出的时候初始化位置
	mainPosition = 1;
	subPosition = -1;				//-1表示没有弹出子菜单
	updateMenu(mainMenuList, APPEAR, mainPosition);
}

void MainMenu::close()
{
	updateMenu(mainMenuList, DISAPPEAR, mainPosition);
	updateMenu(subMenuList, DISAPPEAR, subPosition);
}

void MainMenu::leftMove()
{
	if (subPosition == -1)
	{
		if (mainPosition == 0)
		{
			return;
		}
		mainPosition--;
		updateMenu(mainMenuList, RIGHT_SLIDE, mainPosition);
	} else
	{
		if (subPosition == 0)
		{
			return ;
		}
		subPosition--;
		updateMenu(subMenuList, LEFT_SLIDE, subPosition);
	}
}

void MainMenu::rightMove()
{
	if (subPosition == -1)
	{
		if (mainPosition == 3)
		{
			return;
		}
		mainPosition++;
		updateMenu(mainMenuList, RIGHT_SLIDE, mainPosition);
	} else
	{
		if ((mainPosition == 0 && subPosition == 1)
			|| (mainPosition == 1 && subPosition == 3)
			|| (mainPosition == 2 && subPosition == 1))
		{
			return ;
		}
		subPosition++;
		updateMenu(subMenuList, RIGHT_SLIDE, subPosition);
	}
}

void MainMenu::confirm()
{
	if (subPosition == -1)
	{
		if (mainPosition == 0)
		{
			subPosition = 0;
			initSubMenuData(lyricMenuData, 2);
			updateMenu(mainMenuList, DOWN_SLIDE, mainPosition);
			updateMenu(subMenuList, APPEAR, subPosition);
		} else if (mainPosition == 1)
		{
			subPosition = 0;
			initSubMenuData(bgMenuData, 4);
			updateMenu(mainMenuList, DOWN_SLIDE, mainPosition);
			updateMenu(subMenuList, APPEAR, subPosition);
		} else if (mainPosition == 2)
		{
			subPosition = 0;
			initSubMenuData(weatherMenuData, 2);
			updateMenu(mainMenuList, DOWN_SLIDE, mainPosition);
			updateMenu(subMenuList, APPEAR, subPosition);
		} else if (mainPosition == 3)
		{
			updateMenu(mainMenuList, DISAPPEAR, mainPosition);
			AudioHelper::getInstance()->stopPlay();
		}
	} else {
		if (mainPosition == 0)				//歌词
		{
			if (subPosition == 0)				//展示歌词
			{
				RenderHelper::getInstance()->setLyricLayer(true);
			} else if (subPosition == 1)		//不展示歌词
			{
				RenderHelper::getInstance()->setLyricLayer(false);
			}
		} else if (mainPosition == 1)		//背景
		{
			if (subPosition == 0)				//阴天
			{
				RenderHelper::getInstance()->setSkybox(CLOUDY_LIGHT_RAYS);
			} else if (subPosition == 1)		//风雨交加
			{
				RenderHelper::getInstance()->setSkybox(DARK_STORMY);
			} else if (subPosition == 2)		//雪山
			{
				RenderHelper::getInstance()->setSkybox(SNOW_MOUNTAIN);
			} else if (subPosition == 3)		//夕阳
			{
				RenderHelper::getInstance()->setSkybox(SUN_SET);
			}
		}else if (mainPosition == 2)			//天气
		{
			if (subPosition == 0)				//雨景
			{
				RenderHelper::getInstance()->setWeather(WEATHER_RAIN);
			} else if (subPosition == 1)		//雪景
			{
				RenderHelper::getInstance()->setWeather(WEATHER_SNOW);
			}
		}
		close();
	}
}

void MainMenu::updateMenu(vector<VRMenuItem *> list, enum menuOperation op, int position)
{
	switch(op)
	{
		case APPEAR:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = Spawn::create(MoveTo::create(0.3f, Vec3(100.0*(i-position), 0, -150.0)), ScaleTo::create(0.5f, 1.0f), nullptr);
				list.at(i)->runAction(action);
			}
			state = MENU_ON;
			break;
		}
		case DISAPPEAR:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = Spawn::create(MoveTo::create(0.3f, Vec3(0.f, 0.f, -150.0)), ScaleTo::create(0.5f, 0.01f), nullptr);
				list.at(i)->runAction(action);
			}
			state = MENU_OFF;
			break;
		}
		case LEFT_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveTo::create(0.2f, Vec3(100.0*(i-position), 0, -150.0));
				list.at(i)->runAction(action);
			}
			break;
		}
		case RIGHT_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveTo::create(0.2f, Vec3(100.0*(i-position), 0, -150.0));
				list.at(i)->runAction(action);
			}
			break;
		}
		case UP_SLIDE:
		{	
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveBy::create(0.2f, Vec3(0.f, 100.f, 0.f));
				list.at(i)->runAction(action);
			}
			break;
		}
		case DOWN_SLIDE:
		{
			for (int i = 0; i < list.size(); ++i)
			{
				auto action = MoveBy::create(0.2f, Vec3(0.f, -100.f, 0.f));
				list.at(i)->runAction(action);
			}
			break;
		}
	}
}

void MainMenu::initSubMenuData(string subMenuData[][2], int dataNum) 
{
	//清除原有数据
	for (int i = 0; i < subMenuList.size(); ++i)
	{
		Global::getCurrentScene()->getDefaultCamera()->removeChild(subMenuList.at(i));
	}
	subMenuList.clear();

	for (int i = 0; i < dataNum; ++i)
	{	
		auto item = new VRMenuItem(subMenuData[i][0], subMenuData[i][1]);
		//初始化
		item->setScale(0.f);
		item->setPosition3D(Vec3(0.f, 0.f, -150.f));
		Global::getCurrentScene()->getDefaultCamera()->addChild(item);
		subMenuList.push_back(item);
	}
}

enum MenuState MainMenu::getMenuState()
{
	return state;
}