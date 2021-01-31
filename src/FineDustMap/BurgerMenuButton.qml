import QtQuick 2.0

/**
 *! \brief	BurgerMenuButton in der SearchBar
 *
 * Der Button besteht aus drei schwarzen Rectangles die mit einer Column angeordnet wurden. Mit einer
 * MouseArea wird der Button klickbar gemacht.
 *
 *
 */

Item {
    width: 20
    height: 19
    anchors.top: parent.top
    anchors.topMargin: 22
    anchors.left: parent.left
    anchors.leftMargin: 20

    BaseButton {
        id: burgerButton
        buttonColor: "transparent"
        width: width
        height: height
        pathToImage: stackView.depth > 1 ? "icons/24dp/arrow_back.png" : "icons/24dp/burgermenu.png"
        function execute() {
            if(stackView.depth > 1){
                while(stackView.depth != 1){
                    stackView.pop()
                }
            }
            else {
                print("Burgermenu clicked")
                drawer.open()
                print(stackView.depth)
            }

        }

    }
}
