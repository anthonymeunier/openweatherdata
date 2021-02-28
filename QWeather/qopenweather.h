#ifndef QOPENWEATHER_H
#define QOPENWEATHER_H

#include <QObject>

#include "../libweather/openweathermap.h"
#include "../libweather/weather.h"

class QOpenWeather : public QObject
{
		Q_OBJECT
	public:
		explicit QOpenWeather(QObject *parent = nullptr);
		Q_INVOKABLE float getTemperature(const QString& city);
		Q_INVOKABLE float getFeelsLike(const QString& city);
		Q_INVOKABLE float getWindSpeed(const QString &city);
		Q_INVOKABLE QString getSummary(const QString &city);

	private:
		OpenWeatherMap repository;
		Weather weather;

	signals:

};

#endif // QOPENWEATHER_H
