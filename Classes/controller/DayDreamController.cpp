#include "DayDreamController.h"

void showState(gvr::ControllerState &state)
{
	LOGD("gvr_controller_api_status: %d", state.api_status);
	LOGD("gvr_controller_connection_state: %d", state.connection_state);

	LOGD("orientation: %f %f %f %f", state.orientation.qx, state.orientation.qy, state.orientation.qz, state.orientation.qw);
}

DayDreamController::DayDreamController(VRGvrController *controller) :mController(controller)
{

}

DayDreamController::~DayDreamController()
{
}

void DayDreamController::onUpdate()
{
	gvr::ControllerState state = mController->updateState();
	showState(state);
	
}