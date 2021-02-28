#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

#include "networking.h"
#include "openweathermap.h"
#include "weather.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
	int delay;

	po::options_description options("Allowed options");
	options.add_options()
	        ("help", "produce help message")
	        ("delay", po::value<int>(&delay)->default_value(0), "ping delay")
	        ("city", po::value<std::string>(), "City")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, options), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		std::cout << options << "\n";
		return 0;
	}

	std::string city = vm["city"].as<std::string>();

	Networking networking;
	OpenWeatherMap repository(networking, OpenWeatherMap::getKeyFromFile("apikey.conf"));

	Weather weather(repository);

	for (;;)
	{
		float temperature = weather.temperature(city);
		float feels_like = weather.feels_like(city);
		float windspeed = weather.windspeed(city);
		std::cout << temperature << " " << feels_like << " " << windspeed << "\n";
		if (delay == 0)
		{
			return 0;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	return 0;
}
