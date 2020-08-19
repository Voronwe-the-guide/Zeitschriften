import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width:800
    height: 800
    title: qsTr("Hello World: "+width+"x"+height)
  /*  Rectangle
    {
        anchors.fill: parent
        color: "blue"
    }
*/

    JahreDisplay
    {
        id: jahre
        width: 100
        height: parent.height
    }
  /*  AusgabenDisplay
    {
        id: ausgaben
        width: 50
        height: parent.height
        anchors.left: jahre.right
    }
*/
    ArtikelListDisplay
     {
        id: artikel
        anchors.left: jahre.right
         width: parent.width - jahre.width// -ausgaben.width
         Tracer{}
    }
}
