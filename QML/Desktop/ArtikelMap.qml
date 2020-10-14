import QtQuick 2.0
import QtLocation 5.15
import QtPositioning 5.6
import QtQuick.Dialogs 1.3
import QtQuick.Controls 2.12
//import Qt.labs.location 1.0

Item {
    id: mapDisplay
    property int currenUniqueIndex: -1

    signal coordinatePressed(var latitude, var longitude)
    signal itemSelected(var dbIndex)
    Item
    {
        id: watchMeItem
        property int currenUniqueIndex: mapDisplay.currenUniqueIndex

    }

    function returnCurrentSelectedIndex(index)
    {
        mapDisplay.itemSelected(index);
    }

    function createElement(index)
    {
        var latitude = cArtikelList.getLatitude(index);
        var longitude = cArtikelList.getLongitude(index);
      //  console.log("Get Marker for index: "+index+" : "+latitude+"/"+longitude);
        var component = Qt.createComponent("MapFlag.qml")
        var mapItem = component.createObject(mapDisplay,
                                                 {
                                                     coordinate: QtPositioning.coordinate(latitude,longitude),
                                              autoFadeIn: false,
                                              magazin_text:cArtikelList.getZeitschrift(index),
                                              jahr_text: cArtikelList.getJahr(index),
                                              ausgabe_text: cArtikelList.getAusgabe(index),
                                              seite_text: cArtikelList.getSeite(index),
                                              dbIndex: cArtikelList.getDBIndex(index),
                                              currentIndex: mapDisplay.currenUniqueIndex,
                                              watchMe: watchMeItem
                                             // isCurrent: (mapDisplay.currenUniqueIndex==dbIndex)
                                          });
        if (mapItem != 0)
        {
            mapItem.itemSelected.connect(returnCurrentSelectedIndex) // Ist wie ein Signal/slot -> Die funktion muß die selben Parameter wie das signal haben
        }

        map.addMapItem(mapItem);


    }

    Connections
    {
        target: cArtikelList

        function onListEmpty()
        {
              map.clearMapItems();
        }

        function onElementAdded(index)
        {
            mapDisplay.createElement(index);
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
       Plugin {
            id: mapPlugin
            name: "osm" // "mapboxgl", "esri", ...
       //     PluginParameter { name: "osm.mapping.custom.host"; value: "https://a.tile.openstreetmap.fr/hot" }
            //PluginParameter {name: "osm.mapping.host"; value:"https://www.openstreetmap.de/karte.html"}
            // specify plugin parameters if necessary
            // PluginParameter {
            //     name:
            //     value:
            // }
        }
    //   activeMapType: supportedMapTypes[supportedMapTypes.length - 1]


        //   activeMapType: {stlye: MapType.TerrainMap}
        center: QtPositioning.coordinate(30, 0) // Oslo
        zoomLevel:0



}

    Button
    {
        id: zoomInButton
        width: 50
        height: 50
        icon.source: "qrc:/Images/plus-circle.svg"
   //     text:"+"
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
        width: 50
        height: 50
        icon.source: "qrc:/Images/minus-circle.svg"
//        text: "-"
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        onClicked:
        {
            map.zoomLevel--;
        }

    }




}
