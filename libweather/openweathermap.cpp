#include "openweathermap.h"

#include <fstream>
#include <iostream>
#include <string>

#include <time.h>

float OpenWeatherMap::getTemperature(const std::string& cityname)
{
	City& city = update(cityname);
	return city.temperature;
}

float OpenWeatherMap::getFeelsLike(const std::string& cityname)
{
	City& city = update(cityname);
	return city.feelslike;
}

float OpenWeatherMap::getWindSpeed(const std::string &cityname)
{
	City& city = update(cityname);
	return city.windspeed;
}

std::string OpenWeatherMap::getSummary(const std::string &cityname)
{
	City& city = update(cityname);
	return city.summary;
}

OpenWeatherMap::City::City(boost::json::value& object) :
    name(object.get_object()["name"].get_string().c_str()),
    country(object.get_object()["sys"].get_object()["country"].get_string().c_str()),
    id(static_cast<int>(object.get_object()["id"].get_int64()))
{
	updateFromJson(object);
}

bool OpenWeatherMap::City::isFresh()
{
	time_t timestamp = std::time(nullptr);

	unsigned long seconds = difftime(timestamp, cache_timestamp);
	unsigned long fresh = 60;
	return seconds < fresh;
}
void OpenWeatherMap::City::updateFromJson(boost::json::value &object)
{
	time_t timestamp = std::time(nullptr);
	unsigned long now = difftime(timestamp, 0);

	cache_timestamp = now;
	calculation_timestamp = static_cast<unsigned long>(object.get_object()["dt"].get_int64());
	temperature = static_cast<float>(object.get_object()["main"].get_object()["temp"].get_double());
	feelslike = static_cast<float>(object.get_object()["main"].get_object()["feels_like"].get_double());
	windspeed = static_cast<float>(object.get_object()["wind"].get_object()["speed"].get_double());
	summary = "empty";

	if (object.get_object()["weather"].is_array())
	{
		summary = object.get_object()["weather"].get_array()[0].get_object()["description"].get_string().c_str();
	}
	else
	{
		summary = object.get_object()["weather"].get_object()["description"].get_string().c_str();
	}
}

OpenWeatherMap::City& OpenWeatherMap::update(const std::string& cityname)
{
	auto it = cache.find(cityname);
	if (it == cache.end())
	{
		std::string requesturl = getServiceUrl() + "weather?q=" + cityname + "&appid=" + key;
		std::string result = networking.httprequest(service_domain, requesturl);
		boost::json::value object = boost::json::parse(result);

		City city(object);
		cache[cityname] = std::move(city);
		return cache[cityname];
	}

	City& city = it->second;

	if (not city.isFresh())
	{
		std::string requesturl = getServiceUrl() + "weather?id=" + std::to_string(city.id) + "&appid=" + key;
		std::string result = networking.httprequest(service_domain, requesturl);
		boost::json::value object = boost::json::parse(result);

		city.updateFromJson(object);
	}

	return cache[cityname];
}

std::string OpenWeatherMap::getKeyFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::string line;
	getline(file, line);
	return line;
}

std::string OpenWeatherMap::getServiceUrl()
{
	return "/data/" + std::string(service_version) + "/";
}


OpenWeatherMap weather::fromOpenWeatherMap(const std::string& keyfile)
{
	Networking networking;
	const std::string& key = OpenWeatherMap::getKeyFromFile(keyfile);

	return OpenWeatherMap(networking, key);
}
