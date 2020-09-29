import QtQuick 2.0
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3

Window
{

    id: zeitschriftEditWindow
    width: 600
    height: 400
    visible: true
    modality:Qt.ApplicationModal
    property bool readOnlyMode: false


    title: "Edit Zeitschrift"
    flags:  Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
     |Qt.WindowCancelButtonHint
            | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint

    Row
    {
        id: nameRow
        width: parent.width
        height: 170
        spacing: 10

        Image
        {
            id: zeitschriftLogo
            width: parent.width/2
            height: parent.height-20
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source:  cZeitschriftEditor.logoAdress
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    logoDialog.visible = true
                }
            }


            Rectangle
            {
                id: zeitschriftRamen
                anchors.fill: parent
                color: "transparent"
                border.color: "black"
                RoundButton
                 {
                    id: deleteIconButton
                    text: "X"
                    anchors.right: zeitschriftRamen.right
                    anchors.top:parent.top
                    //color: "red"
                    //anchors.leftMargin: 5
                    width: 25
                    height: 25
                   // icon.color:"red"
                    onClicked:
                    {

                       // cListenController.getOverview();
                        cZeitschriftEditor.setLogoAdress("")
                    }
                    //anchors.verticalCenter: parent.verticalCenter
                 }
            }


        }
        Column
        {
            width: parent.width/2
            height: parent.height-20
            spacing: 10

            IconWithText//DisplayText
            {
                id: titel
                height: parent.height/2-10
                width: parent.width
                toolTip: qsTr("Name der Zeitschrift")
                focus: true
                hasValidData: cZeitschriftEditor.zeitschriftValid
                additionToFont: 5
                font_weight: Font.DemiBold
               // font.bold: true
        //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                text: cZeitschriftEditor.zeitschriftName //+trenner+artikelDisplay.ueberschrift
                readOnly: zeitschriftEditWindow.readOnlyMode
                onTextWasEdited:{cZeitschriftEditor.setName(newText)}
                onNextPressed: {sprache.focus = true}
                onPreviousPressed: {notizen.focus = true}

            }
            IconWithText//DisplayText
            {
                id: sprache
                height: parent.height/2 -10
                width: parent.width
                toolTip: qsTr("Sprache der Zeitschrift")

              //  additionToFont: 5
              //  font_weight: Font.DemiBold
               // font.bold: true
        //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                text: cZeitschriftEditor.sprache //+trenner+artikelDisplay.ueberschrift
                readOnly: zeitschriftEditWindow.readOnlyMode
                onTextWasEdited:{cZeitschriftEditor.setSprache(newText)}
                onNextPressed: {beschreibung.focus = true}
                onPreviousPressed: {titel.focus = true}

            }
        }
    }
    Row
    {
        id: infoRow
        width: parent.width
        height: parent.height - nameRow.height - dialogButtons.height -10
        spacing: 10
        anchors.top:nameRow.bottom
        anchors.topMargin: 10
        BackgroundElement
        {
            id: info_bg
            height: parent.height
                    //-6
            width: parent.width/2-6
            DisplayText_MultiLine
            {
                id: beschreibung
                height: beschreibung.contentHeight + 20
                toolTip: qsTr("Info über die Zeitschrift")


                width: parent.width-6
              //  anchors.centerIn: parent
                text: cZeitschriftEditor.beschreibung
                wrapMode: Text.Wrap
                verticalAlignment: Text.AlignTop
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 2
                 clip: true
                readOnly: zeitschriftEditWindow.readOnlyMode
                onTextWasEdited:{ cZeitschriftEditor.setBeschreibung(newText)}
              onNextPressed: {notizen.focus = true}
               onPreviousPressed: {sprache.focus = true}

            }
        }
        Item
        {
            height: parent.height
            width: 6
        }

        BackgroundElement
        {
            id: notizen_bg
            height: parent.height //-6
            width: parent.width/2-6

            DisplayText_MultiLine
            {
                id: notizen
                height: beschreibung.contentHeight + 20 //parent.height-6
                width: parent.width-6
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 2
                toolTip: qsTr("Notizen")


              //  anchors.centerIn: parent
                 text: cZeitschriftEditor.notiz
                wrapMode: Text.Wrap
                verticalAlignment: Text.AlignTop

                clip: true
                readOnly: zeitschriftEditWindow.readOnlyMode
                onTextWasEdited:{ cZeitschriftEditor.setNotizen(newText)}
                onPreviousPressed: {beschreibung.focus = true}
                onNextPressed: {titel.focus = true}//artikelDisplay.nextPressed()}
              }
          }

    }


    DialogButtonBox
    {
        id: dialogButtons
        signal nextPressed()
        signal previousPressed()
        anchors.bottom: parent.bottom


        Button {
            id: saveButton
            text: qsTr("Speichern")
              DialogButtonBox.buttonRole: DialogButtonBox.AcceptRole
              onClicked:
              {
                 var retVal= cZeitschriftEditor.saveChangesInDB();
                  if (retVal)
                  {
                     zeitschriftEditWindow.close()
                  }
                  else
                  {
                      Qt.createComponent("MessageDisplay.qml").createObject(zeitschriftEditWindow, {text:qsTr("Daten nicht korrekt!")})// artikeleditor.visible = true;

                  }
              }


          }
          Button {
              id: cancelButton
              text: qsTr("Cancel")
              DialogButtonBox.buttonRole: DialogButtonBox.DestructiveRole
              onClicked: { zeitschriftEditWindow.close()}

          }


}

    FileDialog
     {
         id: logoDialog
         title: qsTr("Zeitschriften Logo")
         folder: cZeitschriftEditor.logoAdress==""?cSettings.currentDB:cZeitschriftEditor.logoAdress // shortcuts.home
         selectMultiple: false
         onAccepted: {
             console.log("Adress of Image: "+logoDialog.fileUrl.toString())
             cZeitschriftEditor.setLogoAdress(logoDialog.fileUrl.toString())
             visible: false;
         }
         onRejected: {
            visible: false
         }
     }


}
