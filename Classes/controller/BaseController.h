#pragma once
#include "ControllerInterface.h"

class BaseController
{
public:
	BaseController();
	~BaseController();

protected:
	ControllerInterface *mControllerInterface;
};

