import QtQuick 2.0
import QtPositioning 5.6
import QtLocation 5.15

MapQuickItem
{
id: mapFlag
    width:infoColumn.width //  mapFlag.getWidth(magazin.width,jahr_ausgabe.width,seite.width )// 50
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

/* function getWidth(mag,jahr,seite)
 {
     var middel = 0;
     var result =0;
     if (mag>jahr)
     {
         middle =mag;
     }
     else
     {
         middle = jahr;
     }

     if (middel >seite)
     {
         result = middel;
     }
     else
     {
         result = seite;
     }
     if (result<50)
     {
         result = 50;
     }
     console.log("Result: "+result);
     return result;
 }
*/
 sourceItem: Item
 {
//Tracer{}
    id: displayItem
     width:mapFlag.width//50
    height:mapFlag.height //65
  //x: -25
    y:-height
      Image
     {
       anchors.fill: parent
         source: mapFlag.isCurrent?"qrc:/Images/mapflag_select.svg":"qrc:/Images/mapflag.svg"
     }

     Item
     {
         width: parent.width
         height: parent.height-20
        // color: mapFlag.isCurrent?"red":"transparent"
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
         id: infoColumn
     width: magazin.width>ausgabeColumn.width?magazin.width:ausgabeColumn.width
     height: parent.height

         Text
         {
             id: magazin
              width: contentWidth>50?contentWidth:50 //parent.width
             height: 15
             font.pixelSize: 12
             text: mapFlag.magazin_text
         }
         Column
         {
             id: ausgabeColumn
            width: (jahr_ausgabe.width>seite.width)?jahr_ausgabe.width:seite.width
            height: 30
             Text
             {
                 id: jahr_ausgabe
                 width: contentWidth>50?contentWidth:50 //parent.width
                 height: 15
                 font.pixelSize: 12
                 text: mapFlag.jahr_text+"/"+mapFlag.ausgabe_text
             }
             Text {
                 id: seite
                 width: contentWidth>50?contentWidth:50 //parent.width
                 height: 15
                 font.pixelSize: 12
                 text: qsTr("Seite ")+mapFlag.seite_text
             }
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
