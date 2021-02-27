#include "weather.h"

float Weather::temperature(const std::string& city)
{
	return repository.getTemperature(city) - kelvin;
}

float Weather::feels_like(const std::string& city)
{
	return repository.getFeelsLike(city) - kelvin;
}

float Weather::windspeed(const std::string &city)
{
	return repository.getWindSpeed(city);
}

std::string Weather::summary(const std::string &city)
{
	return repository.getSummary(city);
}
