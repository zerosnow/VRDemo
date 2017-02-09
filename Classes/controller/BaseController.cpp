#include "BaseController.h"

BaseController::BaseController()
{
}

BaseController::~BaseController()
{
}

void BaseController::registerLeft(void(*func)())
{
	onLeftDown = func;
}

void BaseController::registerRight(void(*func)())
{
	onRightDown = func;
}
void BaseController::registerClick(void(*func)())
{
	onClick = func;
}
void BaseController::registerApp(void(*func)())
{
	onAppButton = func;
}