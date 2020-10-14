import QtQuick 2.0
import QtPositioning 5.6
import QtLocation 5.15

MapQuickItem
{
id: mapFlag
    width:50
 height:65
 //x: -25
 y:-height
  property real latitude:59.91
  property real longitude: 10.75
 property string magazin_text: "Magazin"
 property string jahr_text: ""
 property string ausgabe_text: ""
 property string seite_text:""
 property int dbIndex: -1;
 property int currentIndex: -1;
  property QtObject watchMe: null
 property bool isCurrent: dbIndex == watchMe.currenUniqueIndex //false

 z: isCurrent?100000:1

 signal itemSelected(var dbIndex)

 function setCurrent(currentIndex)
 {
     if (currentIndex == mapFlag.dbIndex)
     {
         mapFlag.isCurrent = true;
     }
     else
     {
         mapFlag.isCurrent = false;
     }
 }

 sourceItem: Item
 {
//Tracer{}
     width:50
  height:65
  //x: -25
  y:-height
      Image
     {
       anchors.fill: parent
         source: "qrc:/Images/mapflag.svg"
     }

     Rectangle
     {
         width: parent.width
         height: parent.height-30
         color: mapFlag.isCurrent?"red":"transparent"
         MouseArea
         {
             anchors.fill: parent
             onClicked:
             {
                 itemSelected(dbIndex)
             }
         }
     }

     Column
     {
     width: parent.width
     height: parent.height


 Text
 {
     id: magazin
      width: parent.width
     height: 15
     font.pixelSize: 12
     text: mapFlag.magazin_text
 }
 Text
 {
     id: jahr_ausgabe
     width: parent.width
     height: 15
     font.pixelSize: 12
     text: mapFlag.jahr_text+"/"+mapFlag.ausgabe_text
 }
 Text {
     id: seite
     width: parent.width
     height: 15
     font.pixelSize: 12
     text: qsTr("Seite ")+mapFlag.seite_text
 }



}
 }
// color: "red"

/*Location
{
    id: location
    coordinate{
    latitude: -27.5
           longitude: 153.1
    }
}
*/
}
