#pragma once

class BaseController
{
public:
	BaseController();
	~BaseController();

	void registerLeft(void(*func)());
	void registerRight(void(*func)());
	void registerClick(void(*func)());
	void registerApp(void(*func)());

protected:
	 void (*onLeftDown)();
	 void (*onRightDown)();
	 void (*onClick)();
	 void (*onAppButton)();
};

