#ifndef OPENWEATHERMAP_H
#define OPENWEATHERMAP_H

#include <boost/json.hpp>

#include <fstream>
#include <string>
#include <map>

#include "weatherrepositoryinterface.h"
#include "networking.h"

#include <memory>

class OpenWeatherMap : public WeatherRepositoryInterface
{
	public:	
		OpenWeatherMap(Networking& networking, const std::string& key, const std::string& citylistfile) : networking(networking), key(key)
		{
			std::ifstream cityfile(citylistfile);
			boost::json::stream_parser parser;

			char line[256];
			while (cityfile.getline(line, 256))
			{
				parser.write(line);
			}

			citylist = parser.release();
		}

		float getTemperature(const std::string& city);

		float getFeelsLike(const std::string& city);

		float getWindSpeed(const std::string& city);

		std::string getSummary(const std::string& city);

		static std::string getKeyFromFile(const std::string& filename);

		void print_cache();

	private:
		std::string getServiceUrl();

		float fetchTemperature(int citycode);
		float fetchFeelsLike(int citycode);
		float fetchWindSpeed(int citycode);
		std::string fetchSummary(int citycode);

		unsigned long getTimestamp(int citycode);
		void updateCache(int citycode);
		int getCitycode(const std::string& cityname);

		Networking& networking;

		const char* service_domain = "api.openweathermap.org";
		const char* service_version = "2.5";
		std::string key;
		boost::json::value citylist;
		std::map<int, boost::json::value> cache;

};

#endif // WEATHERREPOSITORY_H
