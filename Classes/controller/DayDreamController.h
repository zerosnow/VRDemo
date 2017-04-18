#pragma once

#include "BaseController.h"
#include "gvr_controller.h"
#include "gvr-sdk/CCVRGvrController.h"
#include "utils/logutil.h"
#include "ControllerInterface.h"

class DayDreamController : public BaseController
{
public:
	DayDreamController(VRGvrController *controller, ControllerInterface *controllerInterface);
	~DayDreamController();

	void onUpdate();

private:
	VRGvrController *mController;
	gvr_vec2f mDownPoint;
};
