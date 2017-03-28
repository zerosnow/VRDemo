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

	snowMountain = TextureCube::create("skybox/left.jpg", "skybox/right.jpg",
        "skybox/top.jpg", "skybox/bottom.jpg",
        "skybox/front.jpg", "skybox/back.jpg");
	snowMountain->retain();
	snowMountain->setTexParameters(tRepeatParams);
	state->setUniformTexture("u_cubeTex", snowMountain);

	//初始化skybox
	skybox = Skybox::create();
	skybox->retain();
	skybox->setTexture(snowMountain);

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
		case SNOW_MOUNTAIN:
			skybox->retain();
			skybox->setTexture(snowMountain);
			break;
		default:
			break;
	}
}

Skybox *SkyboxHelper::getSkybox()
{
	return skybox;
}
