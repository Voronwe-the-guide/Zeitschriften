import QtQuick 2.0

Item
{

    id: jahreDisplay
    width: 50
    height: 800
    property int fontSize: 20

    property int currentJahr: -1

    property int year:0;
    Connections
    {
        target: cJahreList
        function onListEmpty()
        {
            currentJahr = -1;
        }
    }

    Connections
    {
        target: cArtikelEditor
        function onDisplayJahrIndex(index)
        {
            console.log("Neuer Jahr Index"+index)
            if (index>=0)
            {
               console.log("In index");
                jahreList.currentIndex = index;
                jahreList.positionViewAtIndex(jahreList.currentIndex,ListView.Center);
                currentJahr = jahreList.currentIndex

            }
        }
    }

    Component
    {
        id: jahrComponent
        Item
        {
            id: jahrArea
            width: jahreDisplay.width
            height: jahrButton.height + zeitschriftenDisplay.height// + ausgabenForJahrDisplay.height

            Rectangle
            {
                id: jahrButton
                width: parent.width
                height: 30
                color: model.index === currentJahr?"lightblue":"transparent"
                radius: 5

                Text
                {
                    id: jahr
                    anchors.fill: parent

                    text: model.jahr
                     horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize: jahreDisplay.fontSize


                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        jahreDisplay.currentJahr = model.index;
                        jahreList.currentIndex = model.index;
                     //   console.log("Ausgaben request");
                        cArtikelList.deleteAll();
                        cListenController.getLowerInfoForJahr(model.jahr);
                    }
                 }
            }
            ZeitschriftenForJahreDisplay
            {
                id: zeitschriftenDisplay
                anchors.top: jahrButton.bottom
                width: parent.width-20
                anchors.left: parent.left
                anchors.leftMargin: 20
                jahr: model.jahr
                visible: jahreDisplay.currentJahr === model.index

            }

   /*         AusgabenDisplay
            {
                id: ausgabenForJahrDisplay
                anchors.top: zeitschriftenDisplay.bottom//jahrButton.bottom
                width: parent.width-20
                anchors.left: parent.left
                anchors.leftMargin: 20
                visible: jahreDisplay.currentJahr === model.index
             }
     */   }
    }

    ListView
    {
       id: jahreList
        width: parent.width
        height: parent.height
        model: cJahreList
        delegate: jahrComponent
        highlightFollowsCurrentItem : false
        preferredHighlightBegin: height / 2 - 100 // 100 being item height / 2
        preferredHighlightEnd: height / 2 + 100 // 100 being item height / 2
        onCountChanged:
        {
          //  console.log("Jahre count = "+count)
            if (count == 0)
            {
                jahreDisplay.currentJahr = -1;
            }
        }
    }


}
