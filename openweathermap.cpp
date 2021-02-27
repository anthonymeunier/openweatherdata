#include "openweathermap.h"

#include <fstream>
#include <iostream>
#include <string>

#include <time.h>

float OpenWeatherMap::getTemperature(const std::string& city)
{
	return fetchTemperature(getCitycode(city));
}

float OpenWeatherMap::getFeelsLike(const std::string& city)
{
	return fetchFeelsLike(getCitycode(city));
}

float OpenWeatherMap::getWindSpeed(const std::string &city)
{
	return fetchWindSpeed(getCitycode(city));
}

std::string OpenWeatherMap::getSummary(const std::string &city)
{
	return fetchSummary(getCitycode(city));
}


std::string OpenWeatherMap::getKeyFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;
	getline(file, line);
	return line;
}

void OpenWeatherMap::print_cache()
{
	if (cache.empty())
	{
		std::cout << "Cache is empty" << std::endl;
		return;
	}
	for (auto& city : cache)
	{
		std::cout << city.second << std::endl;
	}
}

std::string OpenWeatherMap::getServiceUrl()
{
	return "/data/" + std::string(service_version) + "/";
}

float OpenWeatherMap::fetchTemperature(int citycode)
{
	updateCache(citycode);
	return cache[citycode].get_object()["main"].get_object()["temp"].get_double();
}

float OpenWeatherMap::fetchFeelsLike(int citycode)
{
	updateCache(citycode);
	return cache[citycode].get_object()["main"].get_object()["feels_like"].get_double();
}

float OpenWeatherMap::fetchWindSpeed(int citycode)
{
	updateCache(citycode);
	return cache[citycode].get_object()["wind"].get_object()["speed"].get_double();
}

std::string OpenWeatherMap::fetchSummary(int citycode)
{
	updateCache(citycode);
	boost::json::value& weather = cache[citycode].get_object()["weather"];
	if (weather.is_array())
	{
		return weather.get_array().at(0).get_object()["description"].get_string().c_str();
	}

	return std::string(weather.get_object()["description"].get_string().c_str());
}


unsigned long OpenWeatherMap::getTimestamp(int citycode)
{
	return cache[citycode].get_object()["dt"].get_int64();
}

void OpenWeatherMap::updateCache(int citycode)
{
	bool outdated = false;

	if (cache.find(citycode) == cache.end())
	{
		outdated = true;
	}
	else
	{
		time_t timestamp = time(nullptr);
		unsigned long seconds = difftime(timestamp, getTimestamp(citycode));
		unsigned long fresh = 5*60;
		if (seconds >= fresh)
		{
			outdated = true;
		}
	}

	if (outdated)
	{
		std::string requesturl = getServiceUrl() + "weather?id=" + std::to_string(citycode) + "&appid=" + key;
		std::string result = networking.httprequest(service_domain, requesturl);
		cache[citycode] = boost::json::parse(result);
	}
}

int OpenWeatherMap::getCitycode(const std::string& cityname)
{
	for (auto& citydesc : citylist.get_array())
	{
		if (citydesc.get_object()["name"].get_string() == cityname)
		{
			return citydesc.get_object()["id"].get_int64();
		}
	}
	return 0;
}

