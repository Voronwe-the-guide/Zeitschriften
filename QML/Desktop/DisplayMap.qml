import QtQuick 2.0
import QtLocation 5.15
import QtPositioning 5.6
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.12
//import Qt.labs.location 1.0
Item {
    id: mapDisplay
    property double currentLat: 0;
    property double currentLong: 0;
    property string magazin_text: ""
    property string jahr_text: ""
    property string ausgabe_text: ""
    property string seite_text:""

    signal coordinatePressed(var latitude, var longitude)

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
       Plugin {
            id: mapPlugin
            name: "osm" // "mapboxgl", "esri", ...
            // specify plugin parameters if necessary
            // PluginParameter {
            //     name:
            //     value:
            // }
        }


        //   activeMapType: {stlye: MapType.TerrainMap}
        center: QtPositioning.coordinate(mapFlag.latitude, mapFlag.longitude) // Oslo
        zoomLevel:1


        MouseArea
                {   anchors.fill: parent
                    onClicked:
                    {
                        console.log('latitude = '+ (map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude),
                                           'longitude = '+ (map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude));
                        mapDisplay.coordinatePressed(map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude,map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude)
                    }


                }
 /*https://stackoverflow.com/questions/44862348/how-to-dynamically-set-marker-icon-or-mapcircle-as-fixed-size-for-the-current-lo/44868992*/

        MapFlag{
            id: mapFlag
            latitude: mapDisplay.currentLat;
            longitude: mapDisplay.currentLong;
            magazin_text:mapDisplay.magazin_text
            jahr_text: mapDisplay.jahr_text
            ausgabe_text: mapDisplay.ausgabe_text
            seite_text: mapDisplay.seite_text
            autoFadeIn: false
            coordinate :QtPositioning.coordinate(latitude, longitude) //src.position.coordinate
            opacity:1.0
            visible: !(latitude==0 && longitude==0)

        }

    /*    MapQuickItem {
                id: yeahh
              //  sourceItem: MapFlag
              //  {id: mapIcon;
                    latitude: mapDisplay.currentLat;
                    longitude: mapDisplay.currentLong;
                    magazin_text:mapDisplay.magazin_text
                    jahr_text: mapDisplay.jahr_text
                    ausgabe_text: mapDisplay.ausgabe_text
                    seite_text: mapDisplay.seite_text
               // }
                autoFadeIn: false
                coordinate :QtPositioning.coordinate(mapIcon.latitude, mapIcon.longitude) //src.position.coordinate
                opacity:1.0
                visible: !(mapIcon.latitude==0 && mapIcon.longitude==0)
          //      anchorPoint: Qt.point(sourceItem.width/2, sourceItem.height/2)
            }
*/


     //   }
    }

    Button
    {
        id: zoomInButton
        text:"+"
        anchors.bottom: zoomOutButton.top
        anchors.right: zoomOutButton.right
        onClicked:
        {
            map.zoomLevel++;
        }
    }
    Button
    {
        id: zoomOutButton
        text: "-"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onClicked:
        {
            map.zoomLevel--;
        }

    }


}
