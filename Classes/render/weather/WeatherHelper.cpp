#include "WeatherHelper.h"

WeatherHelper::WeatherHelper(Scene *scene)
{
	FileUtils::getInstance()->addSearchPath("Particle3D/materials");
    FileUtils::getInstance()->addSearchPath("Particle3D/scripts");

	
    _snow = PUParticleSystem3D::create("snow.pu", "pu_mediapack_01.material");
    scene->addChild(_snow);

    _rain = PUParticleSystem3D::create("rainSystem.pu");
    scene->addChild(_rain);
}
WeatherHelper::~WeatherHelper()
{

}

void WeatherHelper::setWeather(enum WeatherType type)
{
	switch(type)
	{
		case WEATHER_SNOW:
		_rain->stopParticleSystem();
		_snow->startParticleSystem();
		break;
    	case WEATHER_RAIN:
		_snow->stopParticleSystem();
		_rain->startParticleSystem();
		break;
    	default:
    	break;
	}
}



