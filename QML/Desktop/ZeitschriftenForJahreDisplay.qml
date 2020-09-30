import QtQuick 2.0

Item
{

    id: zeitschriftenDisplay
    width: 50
 //   height: visible?30*zeitschriftenListe.count:0//zeitschriftArea.height:0// zeitschriftenListe.count* 30:0
    height: visible?currentAusgabenListeHight:0
    property int fontSize: 20
    property int jahr: -1
    property int currentZeitschrift: -1
    property int currentAusgabenListeHight:/*currentZeitschrift===-1?0:*/zeitschriftenListe.contentItem.childrenRect.height //.currentItem.zeitschriftArea.height// zeitschriftenDisplay.currentAusgabenListeHight

    Connections
    {
        target:cZeitschriftenForJahr
        function onListEmpty()
        {
            currentZeitschrift = -1;
        }
    }

    Component
    {
        id: zeitschriftComponent
    //    property variant ausgabenHeight: ausgabenForJahrDisplay.height

        Item
        {
            id: zeitschriftArea
            width:zeitschriftenDisplay.width
            height: zeitschriftButton.height + ausgabenForJahrDisplay.height
            Rectangle
            {
                id:zeitschriftButton
                width: parent.width
                height: 30 //zeitschrift.height + ausgabenForJahrDisplay.height

                color: model.index === currentZeitschrift?"lightblue":"transparent"
                radius: 5
                Text
                {
                    id: zeitschrift
                    text: model.zeitschrift
                    anchors.fill: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: zeitschriftenDisplay.fontSize

                }
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        zeitschriftenDisplay.currentZeitschrift = model.index;
                      //  zeitschriftenDisplay.currentAusgabenListeHight = ausgabenForJahrDisplay.height //.ausgabenHeight
                       //  console.log("Artikel request");
                        cListenController.getAusgabenForZeitschrift(model.zeitschrift, zeitschriftenDisplay.jahr);

                    }
                }
            }
            AusgabenDisplay
            {
                id: ausgabenForJahrDisplay
                anchors.top: zeitschriftButton.bottom//jahrButton.bottom
                width: parent.width-20
                anchors.left: parent.left
                anchors.leftMargin: 20
                visible: zeitschriftenDisplay.currentZeitschrift === model.index
             }

        }

    }

    ListView
    {
       id: zeitschriftenListe
        width: parent.width
        height: parent.height
        model: cZeitschriftenForJahr
        delegate: zeitschriftComponent

        onCountChanged:
        {
            if (count == 0)
            {
                zeitschriftenDisplay.currentZeitschrift = -1;
               // zeitschriftenDisplay.currentAusgabenListeHight = 0;
            }
        }
    }
}

