import QtQuick 2.12
import QtQuick.Window 2.12
import QtLocation 5.12
import QtPositioning 5.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 1.4
import QtQuick.Controls 2.12
import HexagonModel 1.0

/**
 *! \brief	Hauptfenster des Finedust Data Visulization Tools
 *
 * Karte wird angezeigt mithilfe des mapPlugin. Das initialie Item des StackView ist die Map.
 * Mithilfe der Zoombuttons kann auf der Karte rein- und rausgezoomt werden.
 * Es gibt eine Suchleiste ohne Funktion.
 * Das Burgermenu öffnet eine Leiste, in welcher die verschiedenen Daten anhand von Buttons ausgewählt werden können. Diese Daten sollen auf der Karte dann dargestellt werden.
 * Eine Legende auf der Karte erklärt die Bedeutung der Farben der Tiles auf der Karte.
 * Außerdem kann man auf dem Burgermenu auf zwei Buttons drücken, welche zu einem Einstellungsfenster oder einem Graphenfenster führen.
 *
 *
 */

// this is the root

Window {
    id: root
    visible: true
    width: 640
    height: 480
    title: qsTr("Fine Dust Visualization Tool")

    Plugin{
        id: mapPlugin
        name: "osm"

    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: Map {
            id: map
            //anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(51.00, 10.75)
            zoomLevel: 5 // zoom level for germany
            maximumZoomLevel: 14
            minimumZoomLevel: 5
            property var gate: false
            onZoomLevelChanged: {
                hexModel.currentZoomLevel(map.zoomLevel)
                if(map.zoomLevel >= 0 && map.zoomLevel < 7 && gate === false){
                    gate = true;
                    hexContainer.model = modelBT0;
                }
                if(map.zoomLevel >= 7 && map.zoomLevel < 9 && gate === true){
                    gate = false;
                    hexContainer.model = modelBT7;
                }
                if(map.zoomLevel >= 9 && map.zoomLevel < 10 && gate === false){
                    gate = true;
                    hexContainer.model = modelBT9;
                }
                if(map.zoomLevel >= 10 && map.zoomLevel < 12 && gate === true){
                    gate = false;
                    hexContainer.model = modelBT10;
                }
                if(map.zoomLevel >= 12 && gate === false){
                    gate = true;
                    hexContainer.model = modelBT12;
                }
            }
            HexagonModel {
                id: hexModel
            }
            MapItemView {
                id: hexContainer
                model: modelBT0
                delegate: MapPolygon {
                    id: hexagonPolygon
                    color: tileColor
                    opacity: tileOpacity
                    property var temp: valueTemp
                    property var pm25: valuePm25
                    property var pm10: valuePm10
                    property var humidity: valueHumidity

                    path: [
                        { latitude: y0, longitude: x0 },
                        { latitude: y1, longitude: x1 },
                        { latitude: y2, longitude: x2 },
                        { latitude: y3, longitude: x3 },
                        { latitude: y4, longitude: x4 },
                        { latitude: y5, longitude: x5 }
                    ]
                    MouseArea {
                        anchors.fill: parent
                    }

                    states: [State{
                            name: "temperature"; when: temperaturButton.checked
                            PropertyChanges { target: hexagonPolygon; color: hexModel.getTempTileColor(temp)}
                        }, State{
                            name: "pm25"; when: pm25Button.checked
                            PropertyChanges { target: hexagonPolygon; color: hexModel.getPm25TileColor(pm25)}
                        }, State{
                            name: "pm10"; when: pm10Button.checked
                            PropertyChanges { target: hexagonPolygon; color: hexModel.getPm10TileColor(pm10)}
                        }, State{
                            name: "humidity"; when: luftfeuchtigkeitButton.checked
                            PropertyChanges { target: hexagonPolygon; color: hexModel.getHumidityTileColor(humidity)}
                        }]
                }
            }
        }
    }

    /**
     *! \brief	Drawer ist eine Leiste, welche die Buttons für die Sensorauswahl und Weiterleitung zur anderen Fenstern beherbergt.
     */
    Drawer {
        id: drawer
        height: root.height
        width: root.width / 3
        //interactive: stackView.depth === 1

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent
            topMargin: 30

            Column{
                id: columntest
                spacing: 3
                Button {
                    id: backButton
                    flat: true
                    width: 24
                    height: 24
                    Image {
                        id: arrow_back
                        source: "icons/24dp/arrow_back.png"
                    }
                    onClicked: drawer.close()
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    topPadding: 20
                    bottomPadding: 10
                    id: auswahlDatenText
                    text: qsTr("Auswahl Daten")
                }

                Button{
                    id: temperaturButton
                    width: drawer.width - 1
                    height: 30
                    text: qsTr("Temperatur")
                    onClicked: {
                        checked = true
                        drawer.close()
                    }

                }

                Button{
                    id: pm25Button
                    width: drawer.width - 1
                    height: 30
                    text: qsTr("PM 2.5")
                    onClicked: {
                        checked = true
                        drawer.close()
                    }

                }

                Button{
                    id: pm10Button
                    width: drawer.width - 1
                    height: 30
                    text: qsTr("PM 10")
                    onClicked: {
                        checked = true
                        //hexModel.removeHexagons()
                        drawer.close()
                    }

                }

                //                Button{
                //                    id: luftdruckButton
                //                    width: drawer.width - 1
                //                    height: 30
                //                    text: qsTr("Luftdruck")
                //                    onClicked: {
                //                        checked = true
                //                        drawer.close()
                //                    }

                //                }

                Button{
                    id: luftfeuchtigkeitButton
                    width: drawer.width - 1
                    height: 30
                    text: qsTr("Luftfeuchtigkeit")
                    onClicked: {
                        checked = true
                        drawer.close()
                    }

                }

            }
            /**
             *! \brief	ButtonGroup enthält die fünf Buttons für die Sensorauswahl
             */
            ButtonGroup{
                buttons: columntest.children

            }

            Button {
                id: graphButton
                width: drawer.width - 1
                text: qsTr("Graph")
                onClicked: {

                    stackView.push("GraphPage.qml")
                    //print(stackView.depth)
                }
                height: 30
                y: columntest.height + 20

            }

            // TODO: Create window with options for User to change appearance (textsize, textstyle, darkmode, righthandmode) and language of the application.
            //            Button{
            //                id: einstellungenButton
            //                width: drawer.width - 1
            //                text: qsTr("Einstellungen")
            //                onClicked: {

            //                    stackView.push("OptionPage.qml")
            //                    print(stackView.depth)
            //                }
            //                height: 30
            //                y: graphButton.y + 35
            //            }

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    stackView.push(model.source)
                    drawer.close()
                }
            }


            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    SearchBar{
        id: searchbar
    }

    BurgerMenuButton{
    }

    MapLegend{
    }

    ZoomButtons {

    }
}
