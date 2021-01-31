import QtQuick 2.0
import QtQuick.Controls 2.12
import QtLocation 5.12
import QtPositioning 5.2
import SensorManager 1.0


/**
 *! \brief	SearchBar
 *
 * Die SearchBar besteht aus einem weißen Rectangle mit abgerundeten Ecken und einem darüberliegenden TextInput
 *
 * @todo 	Funktionalität der SearchBar implementieren
 */

Item{
    anchors.top: parent.top
    anchors.topMargin: 15
    anchors.left: parent.left
    anchors.leftMargin: 15
    visible: stackView.depth > 1 ? false : true


    TextField {
        background: Rectangle{
            id: rectangle
            width: 200
            height: 30
            color: "white"
            radius: 10
        }
        id: textField
        height: rectangle.height
        x: rectangle.x
        y: rectangle.y
        leftPadding: 40
        width: rectangle.width - 1
        color: "black"
        autoScroll: false
        font.pixelSize: 15
        maximumLength: 22
        placeholderText: qsTr("Stadt")
        onEditingFinished: {
            print("adress entered and saved in string: ", textField.text)
            map.center = sensorManager.getCityCenter(textField.text)
        }
    }

    SensorManager {
        id: sensorManager

    }
}
