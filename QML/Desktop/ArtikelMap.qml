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
    Connections
    {
        target: cArtikelList
        function onListEmpty()
        {
        //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
            artikelList.positionViewAtBeginning();
            artikelList.currentIndex = -1;
            console.log("Empty: Go to 0");
            map.clearMapItems();
        }

        function onElementAdded(index)
        {
        //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
          /*  if (index >1)
            {
                return;
            }
*/
            var latitude = cArtikelList.getLatitude(index);
            var longitude = cArtikelList.getLongitude(index);
            console.log("Get Marker for index: "+index+" : "+latitude+"/"+longitude);
            var Component = Qt.createComponent("MapFlag.qml")
            var item = Component.createObject(mapDisplay,
                                                     {
                                                         coordinate: QtPositioning.coordinate(latitude,longitude),
                                                  autoFadeIn: false,
                                                  magazin_text:cArtikelList.getZeitschrift(index),
                                                  jahr_text: cArtikelList.getJahr(index),
                                                  ausgabe_text: cArtikelList.getAusgabe(index),
                                                  seite_text: cArtikelList.getSeite(index),
                                                  dbIndex: cArtikelList.getDBIndex(index)
                                                         })

           /* {id: mapIcon;
                latitude: mapDisplay.currentLat;
                longitude: mapDisplay.currentLong;
                magazin_text:mapDisplay.magazin_text
                jahr_text: mapDisplay.jahr_text
                ausgabe_text: mapDisplay.ausgabe_text
                seite_text: mapDisplay.seite_text
            }
*/

            map.addMapItem(item);
        }
    }

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
        center: QtPositioning.coordinate(30, 0) // Oslo
        zoomLevel:0


               //  var item2 = Qt.createQmlObject('MapFlag {}', map);
              //  item2.coordinate = QtPositioning.coordinate(cArtikelList.getLatitude(index), cArtikelList.getLongitude(index));
              //  item2.sourceItem = MapFlag
    /*    Connections
        {
            target: cArtikelList
            function onListEmpty()
            {
            //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
                artikelList.positionViewAtBeginning();
                artikelList.currentIndex = -1;
                console.log("Empty: Go to 0");
                map.clearMapItems();
            }

            function onElementAdded(index)
            {
            //    artikelList.positionViewAtIndex(0,artikelList.Beginning);
                if (index >1)
                {
                    return;
                }

                var latitude = cArtikelList.getLatitude(index);
                var longitude = cArtikelList.getLongitude(index);
                console.log("Get Marker for index: "+index+" : "+latitude+"/"+longitude);
                var Component = Qt.createComponent("MapFlag.qml")


                map.addMapItem(item);
            }
        }
     /*   function addMarker(latitude, longitude)
           {
               var Component = Qt.createComponent("qrc:///views/marker.qml")
               var item = Component.createObject(window, {
                                                     coordinate: QtPositioning.coordinate(latitude, longitude)
                                                 })
               map.addMapItem(item)
           }
       */



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