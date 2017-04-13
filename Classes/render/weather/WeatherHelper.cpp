#include "WeatherHelper.h"
#include "utils/Global.h"

WeatherHelper::WeatherHelper()
{
	FileUtils::getInstance()->addSearchPath("Particle3D/materials");
    FileUtils::getInstance()->addSearchPath("Particle3D/scripts");

	
    _snow = PUParticleSystem3D::create("snow.pu", "pu_mediapack_01.material");
    Global::getCurrentScene()->addChild(_snow);

    _rain = PUParticleSystem3D::create("rainSystem.pu");
    Global::getCurrentScene()->addChild(_rain);
}
WeatherHelper::~WeatherHelper()
{

}

void WeatherHelper::setWeather(enum WeatherType type)
{
	mType = type;
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

enum WeatherType WeatherHelper::getWeatherType()
{
	return mType;
}


