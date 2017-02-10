#include "DayDreamController.h"

DayDreamController::DayDreamController(VRGvrController *controller, ControllerInterface *controllerInterface) 
: mController(controller)
{
	mControllerInterface = controllerInterface;
	if (mControllerInterface == nullptr) {
		LOGD("11111");
	} else {
		mControllerInterface->onLeftDown();
	}
}

DayDreamController::~DayDreamController()
{
}

void DayDreamController::onUpdate()
{
	gvr::ControllerState state = mController->updateState();
	if (state.api_status == GVR_CONTROLLER_API_OK 
		&& state.connection_state == GVR_CONTROLLER_CONNECTED)
	{
		// mControllerInterface.updateOrientation(state.orientation);
		// LOGD("orientation: %f %f %f %f", state.orientation.qx, state.orientation.qy, state.orientation.qz, state.orientation.qw);
		if (state.is_touching)
		{
			LOGD("touch_pos: %f, %f", state.touch_pos.x, state.touch_pos.y);
			if (state.touch_pos.x > 0.5)
			{
				mControllerInterface->onRightDown();
			} else {
				mControllerInterface->onLeftDown();
			}
		}
		if (state.button_up[GVR_CONTROLLER_BUTTON_APP])
		{
			mControllerInterface->onAppButton();
		}
	} else {
		// LOGD("gvr_controller_api_status: %d", state.api_status);
		// LOGD("gvr_controller_connection_state: %d", state.connection_state);
	}
	
}