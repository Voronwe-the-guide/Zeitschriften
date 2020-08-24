import QtQuick 2.0

Item
{
    id: artikelDisplay

    width: 600
    height: showColumn.height

    property string zeitschrift:""
    property string jahrgang:""
    property string ausgabe:""
    property string seite: ""
    property string rubrik: ""
    property string kurztext: ""
    property string ueberschrift: ""
    property string zusammenfassung: ""
    property string stichworte:""
    property string author:""
    property string fotos:""
    property string land:""
    property bool   hasGPS: true

    Column
    {
        id: showColumn
        width: parent.width
        height: allgemeineInfo.height + headline.height + detail.height + textInfo.height + countryInfo.height
        property int basicHeight: 25
        Item
        {
            id: allgemeineInfo
            width: parent.width
            height: showColumn.basicHeight
            Tracer{}
            Row
            {
                anchors.fill: parent
                IconWithText
                {
                    id: magazinArea
                    text: artikelDisplay.zeitschrift
                    iconSource: "qrc:/Images/magazin.png"
                    toolTip: qsTr("Magazin")

                }
                IconWithText
                {
                    id: yearArea
                    text: artikelDisplay.jahrgang
                    iconSource: "qrc:/Images/year.png"
                    toolTip: qsTr("Jahr")
                 }

                IconWithText
                {
                   id: editionArea
                   text: artikelDisplay.ausgabe
                   iconSource: "qrc:/Images/edition.png"
                   toolTip: qsTr("Ausgabe")
                }
                IconWithText
                {
                   id:pageArea
                   text: artikelDisplay.seite
                   iconSource: "qrc:/Images/page.png"
                   toolTip: qsTr("Seite")
                }
                IconWithText
                {
                   id: rubrikArea
                   text: artikelDisplay.rubrik
                   iconSource: "qrc:/Images/rubrik.png"
                   toolTip: qsTr("Rubrik")
                }
            }
        }
        Item
        {
            id: countryInfo
            width: parent.width
            height: showColumn.basicHeight
            IconWithText
            {
                id: countyArea
                text: artikelDisplay.land
                iconSource:  "qrc:/Images/land.png"
                toolTip: qsTr("Land")
            }

        }

        Item
        {
            id: textInfo
            width: parent.width
            height: authorArea.height + photoArea.height
            Tracer {bc:"green"}
            Column
            {
               anchors.fill: parent
               IconWithText
                {
                    id: authorArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.author
                    iconSource:  "qrc:/Images/writer.png"
                    toolTip: qsTr("Text von")

                }
               IconWithText
                {
                    id: photoArea
                     height: showColumn.basicHeight
                    text: artikelDisplay.fotos
                    iconSource:  "qrc:/Images/foto.png"
                    toolTip: qsTr("Fotos von")

                }
             }
        }
        Item
        {
            id: headline
            width: parent.width

            height:showColumn.basicHeight + 10
            IconWithText
            {

            }

            DisplayText
            {
              anchors.fill: parent
              font.pixelSize: font.pixelSize+3
              font.bold: true
              property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
              text: artikelDisplay.kurztext+trenner+artikelDisplay.ueberschrift
            }
            Tracer{}

        }
         Item
        {
            id: detail
            width: parent.width
            height: zusammenfassung.height
           Row
           {
            anchors.fill: parent
            BackgroundElement
            {
                height: parent.height-6
                width: parent.width/2-6
                DisplayText
                {
                    id: zusammenfassung
                    height: zusammenfassung.contentHeight + 20//artikelListDisplay.fontSize//>50?zusammenfassungDisplay.contentHeight:50  //parent.height-shortInfoDisplay.height-searchInfoDisplay.height

                  //  height: parent.height-6
                    width: parent.width-6
                    anchors.centerIn: parent
                    text: artikelDisplay.zusammenfassung
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop
                    clip: true

                }
            }
            Item
            {
                height: parent.height
                width: 6
            }

            BackgroundElement
            {
                height: parent.height-6
                width: parent.width/2-6

                DisplayText
                {
                    id: schlagworte
                    height: parent.height-6
                    width: parent.width-6
                    anchors.centerIn: parent
                     text: artikelDisplay.stichworte
                    wrapMode: Text.Wrap
                    verticalAlignment: Text.AlignTop
                    clip: true
                    anchors.left: zusammenfassung.right
                }
              }
           }

        }


    }

}
