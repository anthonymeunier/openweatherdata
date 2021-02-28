#include <iostream>
#include <string>
#include <vector>

#include <thread>
#include <chrono>

#include "libweather.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
	int delay;

	po::options_description options("Allowed options");
	options.add_options()
	        ("help", "Produce help message")
	        ("delay,d", po::value<int>(&delay)->default_value(0), "Ping delay in milliseconds")
	        ("city", po::value<std::string>(), "City")
	;

	po::positional_options_description positional;
	positional.add("city", 1);

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(options).positional(positional).run(), vm);
	po::notify(vm);

	if (vm.count("help") or vm.count("city") != 1)
	{
		std::cout << options << "\n";
		return 0;
	}

	std::string city = vm["city"].as<std::string>();

	std::shared_ptr<Weather> weather = weather::fromOpenWeatherMap("apikey.conf");

	for (;;)
	{
		float temperature = weather->temperature(city);
		float feels_like = weather->feels_like(city);
		float windspeed = weather->windspeed(city);
		std::cout << temperature << " " << feels_like << " " << windspeed << "\n";
		if (delay == 0)
		{
			return 0;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	return 0;
}
