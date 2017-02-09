#pragma once

#include "BaseController.h"
#include "gvr_controller.h"
#include "gvr-sdk/CCVRGvrController.h"
#include "../logutil.h"

class DayDreamController : public BaseController
{
public:
	DayDreamController(VRGvrController *controller);
	~DayDreamController();

	void onUpdate();

private:
	VRGvrController *mController;
};
