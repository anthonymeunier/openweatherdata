#ifndef WEATHERREPOSITORYINTERFACE_H
#define WEATHERREPOSITORYINTERFACE_H

#include <string>

class WeatherRepositoryInterface
{
	public:
		virtual float getTemperature(const std::string& city) = 0;
		virtual float getFeelsLike(const std::string& city) = 0;
		virtual float getWindSpeed(const std::string& city) = 0;
		virtual std::string getSummary(const std::string& city) = 0;
};

#endif // WEATHERREPOSITORYINTERFACE_H
