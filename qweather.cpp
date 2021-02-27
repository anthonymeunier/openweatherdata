#include <iostream>

#include <QCoreApplication>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>

#include "qopenweather.h"

int main(int argc, char** argv)
{
	std::cout << "..:: QWeather ::.." << std::endl;

	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

	QGuiApplication app(argc, argv);
	qmlRegisterType<QOpenWeather>("com.weather", 1, 0, "QOpenWeather");

	QQmlApplicationEngine engine;
	const QUrl url(QStringLiteral("qrc:/mainwindow.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
	                 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
