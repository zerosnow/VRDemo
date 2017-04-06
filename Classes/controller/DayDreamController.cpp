#include "DayDreamController.h"

DayDreamController::DayDreamController(VRGvrController *controller, ControllerInterface *controllerInterface) 
: mController(controller)
{
	mControllerInterface = controllerInterface;
	if (mControllerInterface == nullptr) {
		LOGE("mControllerInterface is null");
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
		mControllerInterface->updateOrientation(state.orientation);
		// LOGD("orientation: %f %f %f %f", state.orientation.qx, state.orientation.qy, state.orientation.qz, state.orientation.qw);
		if (state.is_touching)
		{
			if (state.touch_pos.x > 0.5)
			{
				mControllerInterface->onRightDown();
			} else {
				mControllerInterface->onLeftDown();
			}
		}
		if (state.touch_up)
		{
			mControllerInterface->onTouchUp();
			if (state.touch_pos.x > 0.5)
			{
				mControllerInterface->onRightUp();
			} else {
				mControllerInterface->onLeftUp();
			}
		}
		if (state.button_up[GVR_CONTROLLER_BUTTON_APP])
		{
			mControllerInterface->onAppButtonUp();
		}
	} else {
		// LOGD("gvr_controller_api_status: %d", state.api_status);
		// LOGD("gvr_controller_connection_state: %d", state.connection_state);
	}
	
}