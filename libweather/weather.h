#ifndef WEATHER_H
#define WEATHER_H

#include "providers/weatherrepositoryinterface.h"
#include <string>
#include <memory>

class Weather
{
	public:
		Weather(std::shared_ptr<WeatherRepositoryInterface> repository) : repository(repository)
		{}

		float temperature(const std::string& city);

		float feels_like(const std::string& city);

		float windspeed(const std::string& city);

		std::string summary(const std::string& city);

	private:
		std::shared_ptr<WeatherRepositoryInterface> repository;
		const float kelvin = 273.15;
};

namespace weather
{
	std::shared_ptr<Weather> fromOpenWeatherMap(const std::string& keyfile);
}
#endif // WEATHER_H
