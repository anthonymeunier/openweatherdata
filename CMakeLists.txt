cmake_minimum_required(VERSION 3.5)

project(QOpenWeather LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS json program_options)

add_library(openweather
    libweather/networking/networking.cpp
    libweather/networking/networking.h
    libweather/providers/weatherrepositoryinterface.h
    libweather/providers/OpenWeatherMap/openweathermap.cpp
    libweather/providers/OpenWeatherMap/openweathermap.h
    libweather/weather.cpp
    libweather/weather.h)
target_link_libraries(openweather PRIVATE Threads::Threads Boost::json Boost::program_options)

add_executable(CLIWeather CLIWeather/cli.cpp)
target_link_libraries(CLIWeather PRIVATE openweather)

find_package(Qt5 COMPONENTS Widgets Qml Quick REQUIRED)
add_executable(QWeather
    QWeather/qweather.cpp
    QWeather/resources.qrc
    QWeather/qopenweather.cpp
    QWeather/qopenweather.h)
target_link_libraries(QWeather PRIVATE openweather
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick)
