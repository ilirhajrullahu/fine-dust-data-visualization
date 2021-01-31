import QtQuick 2.0

/**
  this object represents the base class of all buttons in our Application
  properties can be added if need, those
  @author: Baran



  */
Item {

    id: root
    objectName: "Base Button"
    property var buttonWidth: 15
    property var buttonHeight: 15
    property string buttonColor
    property var radius: 0
    property string pathToImage: "..."
    visible: true
    property var base_radius: 0
    property string base_text: ""

    signal click()


    Rectangle{
        id:buttonComponent
        width: root.buttonWidth
        height: root.buttonHeight
        color: root.buttonColor
        visible: true
        radius: root.base_radius

        MouseArea{
            id: mouseAreaComponent
            anchors.fill: parent
            onClicked: {
                // on Click handler
                // this function has to be defined in every BaseButton object and specifies the
                // what happens when the button is clicked
                execute()
            }

        }
        Image{
            id: imageComponent
            source: root.pathToImage
            anchors.centerIn: parent
//            x: parent.x
//            y: parent.y

        }
        Text {
            id: textBox
            text: base_text
            anchors.fill: parent
            visible: base_text === "" ? false : true
        }
    }





}
