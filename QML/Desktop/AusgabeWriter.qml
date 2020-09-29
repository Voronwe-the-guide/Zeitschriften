import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3


Window
{
    id: ausgabeEditWindow
    width: 600
    height: 400
    visible: true
    modality: Qt.ApplicationModal
    property bool readOnlyMode: false


    title: "Edit Ausgabe"
    flags:  Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
     |Qt.WindowCancelButtonHint
            | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint


    Image
    {
        id: cover
        width: parent.width/3
        height: width+(width*2/3)
       // anchors.verticalCenter: parent.verticalCenter
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 25
        fillMode: Image.PreserveAspectFit
        source:  cAusgabeEditor.cover
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                coverDialog.visible = true
            }
        }


        Rectangle
        {
            id: coverRamen
            anchors.fill: parent
            color: "transparent"
            border.color: "black"
            RoundButton
             {
                id: deleteIconButton
                text: "X"
                anchors.right: coverRamen.right
                anchors.top:parent.top
                //color: "red"
                //anchors.leftMargin: 5
                width: 25
                height: 25
               // icon.color:"red"
                onClicked:
                {

                   // cListenController.getOverview();
                    cAusgabeEditor.setCover("")
                }
                //anchors.verticalCenter: parent.verticalCenter
             }
        }


    }

    Item
    {
        id: information_area
        height: parent.height
        width: parent.width-cover.width-50
        anchors.left: cover.right
        anchors.leftMargin: 25
        anchors.top: parent.top
        anchors.topMargin: 10
        property int heightElement: parent.height/8
        Column
        {
            anchors.fill:parent
            spacing: information_area.heightElement/6



           Row
            {
                id: nameElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc:"black"}

                    spacing: 10

                    IconWithText//DisplayText
                    {
                        id: zeitschrift
                        height: parent.height-10
                      //  width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        toolTip: qsTr("Name der Zeitschrift")
                        focus: true
                        hasValidData: cAusgabeEditor.zeitschriftValid
                        additionToFont: 5
                        font_weight: Font.DemiBold
                       // font.bold: true
                //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                        text: cAusgabeEditor.zeitschrift //+trenner+artikelDisplay.ueberschrift
                        readOnly: ausgabeEditWindow.readOnlyMode
                        onTextWasEdited:{cAusgabeEditor.setZeitschrift(newText)}
                        onNextPressed: {untertitel.focus = true}
                        onPreviousPressed: {notizen.focus = true}

                    }


                    IconWithText//DisplayText
                    {
                        id: untertitel
                        height: parent.height*2/3 -10
                      //  width: parent.width
                        toolTip: qsTr("Slogan der Zeitschrift")
                       anchors.verticalCenter: parent.verticalCenter

                      //  additionToFont: 5
                      //  font_weight: Font.DemiBold
                       // font.bold: true
                //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                        text: cAusgabeEditor.untertitel //+trenner+artikelDisplay.ueberschrift
                        readOnly: ausgabeEditWindow.readOnlyMode
                        onTextWasEdited:{cAusgabeEditor.setUntertitel(newText)}
                        onNextPressed: {beschreibung.focus = true}
                        onPreviousPressed: {zeitschrift.focus = true}

                    }

            }
            Item
            {
                id: ausgabeElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc: "red"}
            }
            Item
            {
                id: preisElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc: "blue"}
            }
            Item
            {
                id:redaktionElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc: "green"}
            }
            Item
            {
                id: notizenElement
                height: information_area.heightElement *3
                width: parent.width
                Tracer{bc: "yellow"}
            }


        }

       // Tracer{}
    }

    FileDialog
     {
         id: coverDialog
         title: qsTr("Ausgabe Cover")
         folder: cAusgabeEditor.cover==""?cSettings.currentDB:cAusgabeEditor.cover // shortcuts.home
         selectMultiple: false
         onAccepted: {
             console.log("Adress of Image: "+coverDialog.fileUrl.toString())
             cAusgabeEditor.setCover(coverDialog.fileUrl.toString())
             visible: false;
         }
         onRejected: {
            visible: false
         }
     }
}
