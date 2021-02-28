#ifndef OPENWEATHERMAP_H
#define OPENWEATHERMAP_H

#include <boost/json.hpp>

#include <fstream>
#include <string>
#include <map>

#include "../weatherrepositoryinterface.h"
#include "../../networking/networking.h"

#include <memory>

class OpenWeatherMap : public WeatherRepositoryInterface
{
	public:	
		float getTemperature(const std::string& cityname);

		float getFeelsLike(const std::string& cityname);

		float getWindSpeed(const std::string& cityname);

		std::string getSummary(const std::string& cityname);

		struct City {
			std::string name;
			std::string country;
			int id;
			unsigned long cache_timestamp;
			unsigned long calculation_timestamp;
			float temperature;
			float feelslike;
			float windspeed;
			std::string summary;

			City() {}
			City(boost::json::value& object);

			void updateFromJson(boost::json::value& object);

			bool isFresh();
		};

		OpenWeatherMap(std::shared_ptr<Networking> networking, const std::string& key) : networking(networking), key(key)
		{
		}

		static std::string getKeyFromFile(const std::string& filename);

	private:
		std::string getServiceUrl();

		City& update(const std::string& cityname);

		std::shared_ptr<Networking> networking;

		const char* service_domain = "api.openweathermap.org";
		const char* service_version = "2.5";
		std::string key;
		std::map<std::string, City> cache;

};

namespace weather
{
	namespace repository
	{
		std::shared_ptr<WeatherRepositoryInterface> fromOpenWeatherMap(const std::string& keyfile);
	}
}

#endif // WEATHERREPOSITORY_H
