import QtQuick 2.0
import QtQuick.Controls 2.12

ScrollBar
{
    id: scrollBar;
    width: 30
 policy: ScrollBar.AlwaysOn
 property QtObject connectedScrollElement: parent
 topPadding: 25 + 2
             bottomPadding: 25 + 2

             Rectangle {
                 width: parent.width
                 height: 25
                 color: upButton.pressed ? "lightblue" : "transparent"
                 Image
                 {
                     anchors.fill: parent
                     source:"qrc:/Images/chevron-up.svg"
                 }

                // opacity: vbar.contentItem.opacity

                 MouseArea {
                     id: upButton
                     anchors.fill: parent

                     SmoothedAnimation {
                         target: scrollBar.connectedScrollElement //ausgabenList
                         property: "contentY"
                         running: upButton.pressed
                         velocity: 2000
                         to: 0
                     }


                 }
             }

             Rectangle {
                 y: parent.height - height
                 width: parent.width
                 height: 25
                 color: downButton.pressed ? "lightblue" : "transparent"
            //     opacity: vbar.contentItem.opacity
                Image
                {
                    anchors.fill: parent
                    source:"qrc:/Images/chevron-down.svg"
                }
                 MouseArea {
                     id: downButton
                     anchors.fill: parent

                     SmoothedAnimation {
                         target: scrollBar.connectedScrollElement //ausgabenList
                         property: "contentY"
                         running: downButton.pressed
                         to: scrollBar.connectedScrollElement.contentHeight -scrollBar.connectedScrollElement.height
                         velocity: 2000
                     }



                 }
             }
}
