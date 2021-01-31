import QtQuick 2.0
/**
 *! \brief	OptionPage soll den Benutzer Einstellungen anbieten
 *
 *
 * @todo 	Funktionalität der OptionPage implementieren
 */
Item {
    id: element2
    Rectangle {
        id: test
        color: "#88bcff"
        border.color: "black"
        border.width: 5
        radius: 10
        anchors.rightMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent

        Text {
            id: element3
            x: 196
            y: 186
            width: 249
            height: 109
            text: qsTr("Einstellungsseite Platzhalter")
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            fontSizeMode: Text.FixedSize
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 42
        }
    }

}

