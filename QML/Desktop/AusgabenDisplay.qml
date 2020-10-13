import QtQuick 2.0

Item
{

    id: ausgabenForJahrDisplay
    width: 50
    height: visible?ausgabenListe.count* 30:0

    property int fontSize: 20

    property int currentAusgabe: -1

    Connections
    {
        target: cAusgabenForJahrList
        function onListEmpty()
        {
            currentAusgabe = -1;
        }
    }

    Connections
    {
        target: cArtikelEditor
        function onDisplayAusgabeInJahrIndex(index)
        {
            console.log("Neuer Ausgabe Index"+index)
            if (index>=0)
            {
                console.log("In index");
                ausgabenListe.currentIndex = index;
                ausgabenListe.positionViewAtIndex(ausgabenListe.currentIndex,ListView.Center);
                currentAusgabe = ausgabenListe.currentIndex

            }
        }
    }

    Component
    {
        id: ausgabeComponent
        Rectangle
        {
            id: ausgabeElement
            width: ausgabenForJahrDisplay.width
            height: 30

            color: model.index === currentAusgabe?"lightblue":"transparent"
            radius: 5
            Text
            {
                id: ausgabe
                text: model.ausgabe// + "/"+model.dbIndex
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: ausgabenForJahrDisplay.fontSize

            }
            MouseArea
            {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked:
                {
                    if (mouse.button == Qt.RightButton)
                    {
                        cAusgabeEditor.setForUpdate(model.dbIndex)
                        Qt.createComponent("AusgabeWriter.qml").createObject(ausgabenForJahrDisplay)// artikeleditor.visible = true;
                    }
                    else
                    {
                        ausgabenForJahrDisplay.currentAusgabe = model.index;
                        ausgabenListe.currentIndex = model.index
                    //   console.log("Artikel request");
                        cListenController.getArtikelForAusgabe(model.zeitschrift,model.jahr, model.ausgabe);
                    }
                }
            }
        }
    }

    ListView
    {
       id: ausgabenListe
        width: parent.width
        height: parent.height
        model: cAusgabenForJahrList
        delegate: ausgabeComponent
        highlightFollowsCurrentItem : false
        preferredHighlightBegin: height / 2 - 100 // 100 being item height / 2
        preferredHighlightEnd: height / 2 + 100 // 100 being item height / 2

        onCountChanged:
        {
            if (count == 0)
            {
                ausgabenForJahrDisplay.currentAusgabe = -1;
            }
        }
    }
}
