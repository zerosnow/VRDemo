#pragma once

#include "cocos2d.h"
#include "Particle3D/CCParticleSystem3D.h"
#include "Particle3D/PU/CCPUParticleSystem3D.h"
using namespace cocos2d;

enum WeatherType {
	WEATHER_SNOW,
	WEATHER_RAIN,
	WEATHER_DEFAULT
};

class WeatherHelper
{
public:
	WeatherHelper();
	~WeatherHelper();

	void setWeather(enum WeatherType type);
	enum WeatherType getWeatherType();
private:
	PUParticleSystem3D *_snow;
	PUParticleSystem3D *_rain;
	enum WeatherType mType;
};