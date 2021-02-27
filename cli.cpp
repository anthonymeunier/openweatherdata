#include <iostream>
#include <string>
#include <vector>

#include "networking.h"
#include "openweathermap.h"
#include "weather.h"

int main(int argc, char** argv)
{
	Networking networking;
	OpenWeatherMap repository(networking, OpenWeatherMap::getKeyFromFile("apikey.conf"), "city.list.json");

	Weather weather(repository);
	if (argc == 2)
	{
		std::string city(argv[1]);
		float temperature = weather.temperature(city);
		float feels_like = weather.feels_like(city);
		std::cout << temperature << " " << feels_like << "\n";
		return 0;
	}

	std::cout << "..:: OpenWeather Client ::..\n";
	std::vector<std::string> cities = {"Paris", "London", "Seattle", "Montpellier", "New York"};
	for (auto& city : cities)
	{
		float temperature = weather.temperature(city);
		float feels_like = weather.feels_like(city);
		std::cout << city << ": " << temperature << " (feels like " << feels_like << ")\n";
	}

	return 0;
}
