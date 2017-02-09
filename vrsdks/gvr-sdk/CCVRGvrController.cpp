#include "CCVRGvrController.h"


VRGvrController::VRGvrController()
	: mControllerApi(nullptr)
{
}

VRGvrController::~VRGvrController()
{
}

bool VRGvrController::initController(gvr_context *context)
{
	mControllerApi = std::unique_ptr<gvr::ControllerApi>(new gvr::ControllerApi);
	
	//Set up the options
	gvr::ControllerApiOptions options;
	gvr::ControllerApi::InitDefaultOptions(&options);

	//Enable non-default options
	options.enable_accel = true;

	bool success = mControllerApi->Init(options, context);
	if (!success)
	{
		return false;
	}

	mControllerApi->Resume();
	return true;
}

gvr::ControllerState &VRGvrController::updateState()
{
	mControllerApi->ReadState(&mState);
	return mState;
}

void VRGvrController::Pause()
{
	mControllerApi->Pause();
}

void VRGvrController::Resume()
{
	mControllerApi->Resume();
}