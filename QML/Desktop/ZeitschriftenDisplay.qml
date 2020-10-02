import QtQuick 2.0

Item
{
    id: zeitschriftenDisplay
    property bool horizontal: true
    property int fontSize: 20
    height: 50
    width: parent.width
    Component
    {
        id: zeitschriftenComponent
        Item
        {
            id: zeitschriftenArea
            width: zeitschriftButton.width+10
            height: zeitschriftenDisplay.height


            Rectangle
            {
                id: zeitschriftButton
                width: zeitschrift.contentWidth+30
                height: parent.height-10
                color: model.selected?"lightblue":"lightgrey"
                radius: 5
                anchors.centerIn: parent
              /*  Image
                {
                    anchors.fill: parent
                    source: model.logo
                }
                */
                Text
                {
                    id: zeitschrift
                    anchors.fill: parent

                    text: model.zeitschrift
                     horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pixelSize:  zeitschriftenDisplay.fontSize

                }

                MouseArea
                {
                    anchors.fill: parent
                     acceptedButtons: Qt.LeftButton | Qt.RightButton
                    onClicked:
                    {
                     //   jahreDisplay.currentJahr = model.index;
                     //   console.log("Zeitschriften request");
                        console.log("Area cliecked");
                        if (mouse.button == Qt.RightButton)
                        {
                            cZeitschriftEditor.setForUpdate(model.dbIndex)
                            Qt.createComponent("ZeitschriftWriter.qml").createObject(zeitschriftenDisplay)// artikeleditor.visible = true;
                        }
                        else
                        {
                            cArtikelList.deleteAll();
                            cListenController.addOrRemoveZeitschrift(model.index);
                        }
                    }

                }
            }
        }

    }
    Item
    {
        id: alle
        width: zeitschriftButton.width+10
        height: parent.height

        Rectangle
        {
            id: zeitschriftButton
            width: zeitschrift.contentWidth+30
            height: parent.height-10
            color: "lightgrey"
            radius: 5
            anchors.centerIn: parent

            Text
            {
                id: zeitschrift
                anchors.fill: parent

                text: qsTr("Alle")
                 horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize:  zeitschriftenDisplay.fontSize


            }

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                 //   jahreDisplay.currentJahr = model.index;
                  //  console.log("Zeitschriften request");
               //     cZeitschriftenList.deselectAll();
                    cListenController.getOverview();
                //    cListenController.addOrRemoveZeitschrift(model.index);
                }
             }
        }
    }

    ListView
    {
       id: zeitschriftenListe
       clip: true
       anchors.left: alle.right
        width: parent.width
        height: parent.height
        model: cZeitschriftenList
        delegate: zeitschriftenComponent
        orientation: zeitschriftenDisplay.horizontal?ListView.Horizontal:ListView.Vertical
    }

}
