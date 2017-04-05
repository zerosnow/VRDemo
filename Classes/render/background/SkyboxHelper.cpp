#include "SkyboxHelper.h"

SkyboxHelper::SkyboxHelper()
{

	tRepeatParams.magFilter = GL_LINEAR;
    tRepeatParams.minFilter = GL_LINEAR;
    tRepeatParams.wrapS = GL_CLAMP_TO_EDGE;
    tRepeatParams.wrapT = GL_CLAMP_TO_EDGE;

    //初始化渲染管线
    auto shader = GLProgram::createWithFilenames("cube_map.vert","cube_map.frag");
	state = GLProgramState::create(shader);

	cloudyLightRays = TextureCube::create("skybox/CloudyLightRays/left.png", "skybox/CloudyLightRays/right.png",
        "skybox/CloudyLightRays/top.png", "skybox/CloudyLightRays/bottom.png",
        "skybox/CloudyLightRays/front.png", "skybox/CloudyLightRays/back.png");
	cloudyLightRays->retain();
	cloudyLightRays->setTexParameters(tRepeatParams);
	state->setUniformTexture("u_cubeTex", cloudyLightRays);


	darkStormy = TextureCube::create("skybox/DarkStormy/left.png", "skybox/DarkStormy/right.png",
        "skybox/DarkStormy/top.png", "skybox/DarkStormy/bottom.png",
        "skybox/DarkStormy/front.png", "skybox/DarkStormy/back.png");
	darkStormy->retain();
	darkStormy->setTexParameters(tRepeatParams);
	state->setUniformTexture("u_cubeTex", darkStormy);

	snowMountain = TextureCube::create("skybox/SnowMountain/left.jpg", "skybox/SnowMountain/right.jpg",
        "skybox/SnowMountain/top.jpg", "skybox/SnowMountain/bottom.jpg",
        "skybox/SnowMountain/front.jpg", "skybox/SnowMountain/back.jpg");
	snowMountain->retain();
	snowMountain->setTexParameters(tRepeatParams);
	state->setUniformTexture("u_cubeTex", snowMountain);

	sunSet = TextureCube::create("skybox/SunSet/left.png", "skybox/SunSet/right.png",
        "skybox/SunSet/top.png", "skybox/SunSet/bottom.png",
        "skybox/SunSet/front.png", "skybox/SunSet/back.png");
	sunSet->retain();
	sunSet->setTexParameters(tRepeatParams);
	state->setUniformTexture("u_cubeTex", sunSet);

	//初始化skybox
	skybox = Skybox::create();
	skybox->setPosition3D(Vec3(0, 100, 0));
}

SkyboxHelper::~SkyboxHelper()
{
	delete snowMountain;
	delete skybox;
}

void SkyboxHelper::setSkybox(enum SkyboxType type)
{
	switch(type) 
	{
		case CLOUDY_LIGHT_RAYS:
			skybox->retain();
			skybox->setTexture(cloudyLightRays);
			break;
		case DARK_STORMY:
			skybox->retain();
			skybox->setTexture(darkStormy);
			break;
		case SNOW_MOUNTAIN:
			skybox->retain();
			skybox->setTexture(snowMountain);
			break;
		case SUN_SET:
			skybox->retain();
			skybox->setTexture(sunSet);
			break;
		default:
			break;
	}
}

Skybox *SkyboxHelper::getSkybox()
{
	return skybox;
}
