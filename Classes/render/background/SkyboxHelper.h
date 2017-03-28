#pragma once

#include "cocos2d.h"
using namespace cocos2d;

enum SkyboxType {
	SNOW_MOUNTAIN, 
	DEFAULT
};

class SkyboxHelper
{
public:
	SkyboxHelper();
	~SkyboxHelper();

	void setSkybox(enum SkyboxType type);
	Skybox *getSkybox();
	
private:
	TextureCube *snowMountain;
	Texture2D::TexParams tRepeatParams;
	GLProgramState *state;
	Skybox *skybox;
};