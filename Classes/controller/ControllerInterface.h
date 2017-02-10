#pragma once

#include "gvr_types.h"
#include "../logutil.h"

class ControllerInterface
{
public:
	virtual void onLeftDown() = 0;
	virtual void onRightDown() = 0;
	virtual void onAppButton() = 0;
	virtual void updateOrientation(gvr_quatf orientation) = 0;
};