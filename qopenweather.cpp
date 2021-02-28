#include "qopenweather.h"

QOpenWeather::QOpenWeather(QObject *parent) : QObject(parent), repository(networking, OpenWeatherMap::getKeyFromFile("apikey.conf")), weather(repository)
{

}

Q_INVOKABLE float QOpenWeather::getTemperature(const QString& city)
{
	return weather.temperature(city.toStdString());
}

Q_INVOKABLE float QOpenWeather::getFeelsLike(const QString &city)
{
	return weather.feels_like(city.toStdString());
}

Q_INVOKABLE float QOpenWeather::getWindSpeed(const QString &city)
{
	return weather.windspeed(city.toStdString());
}

Q_INVOKABLE QString QOpenWeather::getSummary(const QString &city)
{
	return QString::fromStdString(weather.summary(city.toStdString()));
}
