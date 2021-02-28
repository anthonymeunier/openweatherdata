#include "libweather.h"
#include <boost/python.hpp>

BOOST_PYTHON_MODULE(libweatherpy)
{
	using namespace boost::python;
	def("fromOpenWeatherMap", &weather::fromOpenWeatherMap);
	class_<Weather>("Weather", no_init)
	        .def("temperature", &Weather::temperature)
	        .def("feels_like", &Weather::feels_like)
	        .def("windspeed", &Weather::windspeed)
	        .def("summary", &Weather::summary)
	;
}


