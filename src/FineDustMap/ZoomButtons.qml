import QtQuick 2.0

/**
 *! \brief	zoomIn und zoomOut Buttons
 *
 * Die zoomIn und zoomOut Buttons befinden sich in einer Column damit nur die Column ausgerichtet werden muss.
 * Die Buttons bestehen aus einem Rectangle das mit einer MouseArea klickbar gemacht wurde und einem Text für
 * die Beschriftung der Buttons. Die Größe und Hintergrundfarbe der Buttons können mit den Variablen buttonWidth,
 * buttonHeight und buttonColor geändert werden.
 *
 * @buttonWidth 30      Breite von 30px
 * @buttonHeight 30 	Höhe von 30px
 * @buttonColor "grey" 	Hintergrundfarbe grau
 *
 */

Item {


    property var m_buttonWidth: 30
    property var m_buttonHeight: 30
    property var m_buttonColor: "grey"
    property var m_radius: 3

    anchors.right: parent.right
    anchors.rightMargin: 60
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 40

    id: buttonRow

    BaseButton{
        id: plusButton
        objectName: "Zoom in Button"
        buttonColor: m_buttonColor
        buttonHeight: m_buttonHeight
        buttonWidth: m_buttonHeight
        pathToImage: "icons/24dp/plus.png"
        base_radius: m_radius
        visible: stackView.depth > 1 ? false : true

        anchors.right: parent.right
        anchors.bottom: buttonRow.bottom
        anchors.bottomMargin: 40
        function execute(){
            if(map.zoomLevel <= 13){
                map.zoomLevel++
            }
            if(map.zoomLevel > 13 && map.zoomLevel < 14){
                map.zoomLevel = 14;
            }

        }
    }
    BaseButton{
        id: zoomOutButton
        objectName: "Zoom out Button"
        buttonColor: m_buttonColor
        buttonHeight: m_buttonHeight
        buttonWidth: m_buttonWidth
        pathToImage: "icons/24dp/minus.png"
        base_radius: m_radius
        visible: stackView.depth > 1 ? false : true
        function execute(){
            if(map.zoomLevel >= 6){
                map.zoomLevel--
            }
            if(map.zoomLevel > 5 && map.zoomLevel < 6){
                map.zoomLevel = 5;
            }

        }

    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
