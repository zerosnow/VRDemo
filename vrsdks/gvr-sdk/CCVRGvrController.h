#pragma once

#include "gvr/include/gvr_controller.h"

class VRGvrController
{
public:
	VRGvrController();
	~VRGvrController();

	bool initController(gvr_context *context);
	virtual gvr::ControllerState &updateState();

	void Pause();
	void Resume();

private:
	gvr::ControllerState mState;
	std::unique_ptr<gvr::ControllerApi> mControllerApi;
};