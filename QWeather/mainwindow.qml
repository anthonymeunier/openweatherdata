import QtQuick 2.12
import QtQuick.Controls 2.5
import com.weather 1.0
import QtQuick.Layouts 1.11

ApplicationWindow {
    id: applicationWindow
    width: 400
    height: 500
    visible: true
    title: qsTr("QWeather")

    QOpenWeather {
        id: myopenweather
    }

    Column {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 2
            TextField {
                id: city_input
                placeholderText: "City"
                anchors.left: parent.left
                anchors.right: parent.right
            }

            Button {
                id: button
                text: qsTr("Get")
                anchors.left: parent.left
                anchors.right: parent.right
                onClicked: {
                    cityname.text = city_input.text
                    summary.text = myopenweather.getSummary(city_input.text)
                    temperature.text = myopenweather.getTemperature(city_input.text).toFixed(2) + "°C"
                    feels_like.text = myopenweather.getFeelsLike(city_input.text).toFixed(2) + "°C"
                    windspeed.text = myopenweather.getWindSpeed(city_input.text).toFixed(2) + " meter/sec"
                }
            }

        Frame {
            id: frame_cityname
            anchors.left: parent.left
            anchors.right: parent.right
            Column {
                anchors.fill: parent
                Text {
                    id: cityname
                    text: qsTr("")
                    font.pixelSize: 20
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
                Text {
                    id: summary
                    text: qsTr("")
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
            }


        }

        Frame {
            id: frame_temperature
            anchors.left: parent.left
            anchors.right: parent.right
            Grid {
                columns: 2

                Text {
                    id: temperature_field
                    text: qsTr("Temperature")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
                Text {
                    id: temperature
                    text: qsTr("")
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
                Text {
                    id: feelslike_field
                    text: qsTr("Feels like")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
                Text {
                    id: feels_like
                    text: qsTr("")
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
            }
        }
        Frame {
            id: frame_wind
            anchors.left: parent.left
            anchors.right: parent.right
            Grid {
                columns: 2

                Text {
                    id: windspeed_field
                    text: qsTr("Wind Speed")
                    font.pixelSize: 14
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
                Text {
                    id: windspeed
                    text: qsTr("")
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                    padding: 6
                }
            }
        }
    }
}




