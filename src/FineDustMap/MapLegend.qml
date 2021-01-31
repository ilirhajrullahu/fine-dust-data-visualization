import QtQuick 2.0
import QtGraphicalEffects 1.12

/**
 *! \brief	Legende auf der Karte
 *
 * Der gesamte Inhalt der Legende befindet sich in einem Item (id: legendContainer) um das Layout auf der Karte besser anpassen zu
 * können. Das Item wird mit einem Rectangle (id: legendBackground) ausgefüllt und dient als Hintergrund der Legende. Die Skala
 * mit Beschriftung befindet sich im Item mit der id: scale. Die Skala besteht aus einem Rectangle das mit einem Farbverlauf entsprechend
 * der angezeigenten Messwerte eingefärbt wird. Es gibt insgesamt 6 Textfelder für die Beschriftung. Je nachdem welcher Button
 * gedrückt wurde ändern sich die Farben der Skala, die Beschriftung der Textfelder und die Position der Textfelder.
 *
 * @colorArray ["red", "orange", "yellow", "green", "cyan", "blue"]      Array zum Speichern verschiedener Farben für die Legende
 *
 * @todo 	Farbverläufe verbessern
 */

Item {
    id: legendContainer
    width: 83
    height: 150
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 25
    anchors.left: parent.left
    anchors.leftMargin: 15
    visible: stackView.depth > 1 ? false : true
    Rectangle {
        id: legendBackground
        color: "white"
        radius: 10
        opacity: 0.8
        anchors.fill: parent
    }

    Item {
        id: scale
        property variant colorArray: ["purple", "purple", "purple", "red", "red", "red", "red" ,"orange" ,"orange" ,"#0a635d" ,"#0a635d"]

        Rectangle {
            id: temperatureScale
            width: legendContainer.width * 0.25
            height: legendContainer.height * 0.9
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.left: parent.left
            anchors.leftMargin: 10
            gradient: Gradient {
                GradientStop { position: 0.0; color: scale.colorArray[0] }
                GradientStop { position: 0.1; color: scale.colorArray[1] }
                GradientStop { position: 0.2; color: scale.colorArray[2] }
                GradientStop { position: 0.3; color: scale.colorArray[3] }
                GradientStop { position: 0.4; color: scale.colorArray[4] }
                GradientStop { position: 0.5; color: scale.colorArray[5] }
                GradientStop { position: 0.6; color: scale.colorArray[6] }
                GradientStop { position: 0.7; color: scale.colorArray[7] }
                GradientStop { position: 0.8; color: scale.colorArray[8] }
                GradientStop { position: 0.9; color: scale.colorArray[9] }
                GradientStop { position: 1.0; color: scale.colorArray[10] }
            }
        }
        Text {
            id: text1
            text: qsTr("_ 500")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -146
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }
        Text {
            id: text2
            text: qsTr("_ 100")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -119.4
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }
        Text {
            id: text3
            text: qsTr("_ 75")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -92.8
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }
        Text {
            id: text4
            text: qsTr("_ 50")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -66.2
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }
        Text {
            id: text5
            text: qsTr("_ 25")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -39.6
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }
        Text {
            id: text6
            text: qsTr("_ -0 µg/m³")
            anchors.top: temperatureScale.bottom
            anchors.topMargin: -13
            anchors.left: temperatureScale.right
            anchors.leftMargin: 1
        }

    }

    states: [State{
            name: "temperature"; when: temperaturButton.checked
            PropertyChanges { target: scale; colorArray: ["red", "red", "orange", "orange", "yellow", "yellow", "green", "cyan", "cyan", "blue", "blue"]}
            PropertyChanges { target: text1; text: qsTr("_ 40"); anchors.topMargin: -146}
            PropertyChanges { target: text2; text: qsTr("_ 30"); anchors.topMargin: -119.4}
            PropertyChanges { target: text3; text: qsTr("_ 20"); anchors.topMargin: -92.8}
            PropertyChanges { target: text4; text: qsTr("_ 10"); anchors.topMargin: -66.2}
            PropertyChanges { target: text5; text: qsTr("_ 0"); anchors.topMargin: -39.6}
            PropertyChanges { target: text6; text: qsTr("_ -20 °C"); anchors.topMargin: -13}
        }, State{
            name: "pm25"; when: pm25Button.checked
            PropertyChanges { target: scale; colorArray: ["purple", "purple", "purple", "red", "red", "red", "red" ,"orange" ,"orange" ,"#0a635d" ,"#0a635d"]}
            PropertyChanges { target: text1; text: qsTr("_ 500"); anchors.topMargin: -146}
            PropertyChanges { target: text2; text: qsTr("_ 100"); anchors.topMargin: -119.4}
            PropertyChanges { target: text3; text: qsTr("_ 75"); anchors.topMargin: -92.8}
            PropertyChanges { target: text4; text: qsTr("_ 50"); anchors.topMargin: -66.2}
            PropertyChanges { target: text5; text: qsTr("_ 25"); anchors.topMargin: -39.6}
            PropertyChanges { target: text6; text: qsTr("_ 0 µg/m³"); anchors.topMargin: -13}
        }, State{
            name: "pm10"; when: pm10Button.checked
            PropertyChanges { target: scale; colorArray: ["purple", "purple", "red", "red", "red", "red", "orange" ,"orange" ,"#0a635d" ,"#0a635d" ,"#0a635d"]}
            PropertyChanges { target: text1; text: qsTr("_ 500"); anchors.topMargin: -146}
            PropertyChanges { target: text2; text: qsTr("_ 100"); anchors.topMargin: -119.4}
            PropertyChanges { target: text3; text: qsTr("_ 75"); anchors.topMargin: -92.8}
            PropertyChanges { target: text4; text: qsTr("_ 50"); anchors.topMargin: -66.2}
            PropertyChanges { target: text5; text: qsTr("_ 25"); anchors.topMargin: -39.6}
            PropertyChanges { target: text6; text: qsTr("_ 0 µg/m³"); anchors.topMargin: -13}
//        }, State{
//            name: "pressure"; when: luftdruckButton.checked
//            PropertyChanges { target: scale; colorArray: ["#423213", "orange", "orange", "yellow", "yellow", "green", "cyan" ,"cyan" ,"blue" ,"purple" ,"purple"]}
//            PropertyChanges { target: text1; text: qsTr("_ 1100"); anchors.topMargin: -146}
//            PropertyChanges { target: text2; text: qsTr("_ 1057"); anchors.topMargin: -112.75}
//            PropertyChanges { target: text3; text: qsTr("_ 1013"); anchors.topMargin: -79.5}
//            PropertyChanges { target: text4; text: qsTr("_ 970"); anchors.topMargin: -46.25}
//            PropertyChanges { target: text5; text: qsTr("_ 926 hPa"); anchors.topMargin: -13}
//            PropertyChanges { target: text6; text: qsTr(""); anchors.topMargin: 0}

        }, State{
            name: "humidity"; when: luftfeuchtigkeitButton.checked
            PropertyChanges { target: scale; colorArray: ["blue", "cyan", "cyan", "green", "green", "yellow", "yellow" ,"orange" ,"orange" ,"red" ,"red"]}
            PropertyChanges { target: text1; text: qsTr("_ 100"); anchors.topMargin: -146}
            PropertyChanges { target: text2; text: qsTr("_ 80"); anchors.topMargin: -119.4}
            PropertyChanges { target: text3; text: qsTr("_ 60"); anchors.topMargin: -92.8}
            PropertyChanges { target: text4; text: qsTr("_ 40"); anchors.topMargin: -66.2}
            PropertyChanges { target: text5; text: qsTr("_ 20"); anchors.topMargin: -39.6}
            PropertyChanges { target: text6; text: qsTr("_ 0 %"); anchors.topMargin: -13}
        }]
}
