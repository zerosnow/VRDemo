#pragma once

#include "gvr_types.h"
#include "utils/logutil.h"

class ControllerInterface
{
public:
	virtual void onLeftDown() = 0;
	virtual void onRightDown() = 0;
	virtual void onLeftUp() = 0;
	virtual void onRightUp() = 0;
	virtual void onAppButtonUp() = 0;
	virtual void onTouchUp() = 0;
	virtual void updateOrientation(gvr_quatf orientation) = 0;
};