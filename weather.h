#ifndef WEATHER_H
#define WEATHER_H

#include "weatherrepositoryinterface.h"
#include <string>

class Weather
{
	public:
		Weather(WeatherRepositoryInterface& repository) : repository(repository)
		{}

		float temperature(const std::string& city);

		float feels_like(const std::string& city);

		float windspeed(const std::string& city);

		std::string summary(const std::string& city);

	private:
		WeatherRepositoryInterface& repository;
		const float kelvin = 273.15;
};

#endif // WEATHER_H
