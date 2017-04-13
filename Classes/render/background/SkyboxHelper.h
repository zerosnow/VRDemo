#pragma once

#include "cocos2d.h"
using namespace cocos2d;

enum SkyboxType {
	CLOUDY_LIGHT_RAYS,
	DARK_STORMY,
	SNOW_MOUNTAIN,
	SUN_SET, 
	DEFAULT
};

class SkyboxHelper
{
public:
	SkyboxHelper();
	~SkyboxHelper();

	void setSkybox(enum SkyboxType type);
	Skybox *getSkybox();
	enum SkyboxType getSkyboxType();
	
private:
	TextureCube *cloudyLightRays;
	TextureCube *darkStormy;
	TextureCube *snowMountain;
	TextureCube *sunSet;

	Texture2D::TexParams tRepeatParams;
	GLProgramState *state;
	Skybox *skybox;

	enum SkyboxType mType;
};