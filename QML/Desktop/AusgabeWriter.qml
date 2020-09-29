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


    Item
    {
        id: nameElement
        width: information_area.width
        height: information_area.heightElement
        Row
            {
               // id: nameElement
                anchors.fill: parent
              //  height: information_area.heightElement
               // width: parent.width
                Tracer{bc:"black"}

                 //   spacing: 10

                    IconWithText//DisplayText
                    {
                        id: zeitschrift
                        height: parent.height-10
                   //     width: 100 //parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        toolTip: qsTr("Name der Zeitschrift")
                        focus: true
                        hasValidData: cAusgabeEditor.zeitschriftValid
                        additionToFont: 5
                        font_weight: Font.DemiBold
                       //font.bold: true
                //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                        text: cAusgabeEditor.zeitschrift //+trenner+artikelDisplay.ueberschrift
                        readOnly: ausgabeEditWindow.readOnlyMode
                        onTextWasEdited:{cAusgabeEditor.setZeitschrift(newText)}
                        onNextPressed: {untertitel.focus = true}
                        onPreviousPressed: {notizen.focus = true}
                        onWidthChanged:
                        {
                            console.log(width)
                        }


                    }


                    IconWithText//DisplayText
                    {
                        id: untertitel

                       height: parent.height*2/3 -10
                      //  width: parent.width
                        toolTip: qsTr("Slogan der Zeitschrift")
                       anchors.verticalCenter: parent.verticalCenter
                       anchors.left: zeitschrift.right

                      //  additionToFont: 5
                      //  font_weight: Font.DemiBold
                       // font.bold: true
                //        property string trenner: ((artikelDisplay.kurztext!="") && (artikelDisplay.ueberschrift!=""))?": ":""
                        text: cAusgabeEditor.untertitel //+trenner+artikelDisplay.ueberschrift
                        readOnly: ausgabeEditWindow.readOnlyMode
                        onTextWasEdited:{cAusgabeEditor.setUntertitel(newText)}
                        onNextPressed: {yearArea.focus = true}
                        onPreviousPressed: {zeitschrift.focus = true}

                    }

            }
    }
            Item
            {
                id: ausgabeElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc: "red"}
                Row
                    {
                       // id: nameElement
                      width: parent.width //  anchors.fill: parent
                        spacing: 4
                        height: 25
                        IconWithText
                        {
                            id: yearArea
                            text: ( cAusgabeEditor.jahr==0)?"":cAusgabeEditor.jahr
                            iconSource: "qrc:/Images/year.svg"//.png"
                            toolTip: qsTr("Erscheinungsjahr")
                            readOnly:ausgabeEditWindow.readOnlyMode
                            onTextWasEdited:{ cAusgabeEditor.setJahr(newText)}
                            onNextPressed: {editionArea.focus = true}
                            onPreviousPressed: {untertitel.focus = true}
                            hasValidData:  cAusgabeEditor.jahrValid
                         }

                        IconWithText
                        {
                           id: editionArea
                           text: (cAusgabeEditor.ausgabe==0)?"":cAusgabeEditor.ausgabe
                           iconSource: "qrc:/Images/edition.svg"  //.png"
                           toolTip: qsTr("Ausgabe im Jahr")
                           readOnly: ausgabeEditWindow.readOnlyMode
                           onTextWasEdited:{ cAusgabeEditor.setAusgabe(newText)}
                           onNextPressed: {pageArea.focus = true}
                           onPreviousPressed: {yearArea.focus = true}
                           hasValidData: cAusgabeEditor.isAusgabeValid()
                        }
                        IconWithText
                        {
                           id:pageArea
                           text: (cAusgabeEditor.seitenzahl==0)?"":cAusgabeEditor.seitenzahl
                           iconSource: "qrc:/Images/page.svg"  //.png"
                           toolTip: qsTr("Anzahl der Seiten")
                           readOnly:ausgabeEditWindow.readOnlyMode
                           onTextWasEdited:{ cAusgabeEditor.setSeitenzahl(newText)}
                           onNextPressed: {preisArea.focus = true}
                           onPreviousPressed: {editionArea.focus = true}

                        }
                    }


            }
            Item
            {
                id: preisElement
                height: information_area.heightElement
                width: parent.width
                Row
                    {
                       // id: nameElement
                      width: parent.width //  anchors.fill: parent
                        spacing: 4
                        height: 25
                        IconWithText
                        {
                            id: preisArea
                            text:  cAusgabeEditor.preis// r==0)?"":cAusgabeEditor.jahr
                            iconSource: "qrc:/Images/year.svg"//.png"
                            toolTip: qsTr("Preis")
                            readOnly:ausgabeEditWindow.readOnlyMode
                            onTextWasEdited:{ cAusgabeEditor.setPreis(newText)}
                            onPreviousPressed: {pageArea.focus = true}
                            onNextPressed: {waehrungArea.focus = true}

                         }

                        IconWithText
                        {
                           id: waehrungArea
                           text: cAusgabeEditor.waehrung //.ausgabe==0)?"":cAusgabeEditor.ausgabe
                           iconSource: "qrc:/Images/edition.svg"  //.png"
                           toolTip: qsTr("Währung")
                           readOnly: ausgabeEditWindow.readOnlyMode
                           onTextWasEdited:{ cAusgabeEditor.setWaehrung(newText)}
                          onPreviousPressed : {preisArea.focus = true}
                           onNextPressed: {languageArea.focus = true}

                        }
                        IconWithText
                        {
                           id:languageArea
                           text: cAusgabeEditor.sprache //eitenzahl==0)?"":cAusgabeEditor.seitenzahl
                           iconSource: "qrc:/Images/page.svg"  //.png"
                           toolTip: qsTr("Sprache")
                           readOnly:ausgabeEditWindow.readOnlyMode
                           onTextWasEdited:{ cAusgabeEditor.setSprache(newText)}
                           onNextPressed: {redakteurArea.focus = true}
                           onPreviousPressed: {waehrungArea.focus = true}

                        }
                    }               Tracer{bc: "blue"}

            }
            Item
            {
                id:redaktionElement
                height: information_area.heightElement
                width: parent.width
                Tracer{bc: "green"}
                IconWithText
                {
                   id:redakteurArea
                   height: 25
                   text: cAusgabeEditor.chefredakteur //eitenzahl==0)?"":cAusgabeEditor.seitenzahl
                   iconSource: "qrc:/Images/page.svg"  //.png"
                   toolTip: qsTr("Chefredaktion")
                   readOnly:ausgabeEditWindow.readOnlyMode
                   onTextWasEdited:{ cAusgabeEditor.setChefredakteur(newText)}
                   onNextPressed: {notizen.focus = true}
                   onPreviousPressed: {languageArea.focus = true}

                }
            }
            Item
            {
                id: notizenElement
                height: information_area.heightElement *3
                width: parent.width
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
                         text: cAusgabeEditor.notizen
                        wrapMode: Text.Wrap
                        verticalAlignment: Text.AlignTop

                        clip: true
                                readOnly:ausgabeEditWindow.readOnlyMode
                        onTextWasEdited:{ cZeitschriftEditor.setNotizen(newText)}
                        onPreviousPressed: {redakteurArea.focus = true}
                        onNextPressed: {zeitschrift.focus = true}//artikelDisplay.nextPressed()}
                      }
                  }

                Tracer{bc: "yellow"}
            }


        }

       // Tracer{}
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
                 var retVal= cAusgabeEditor.saveChangesInDB();
                  if (retVal)
                  {
                     ausgabeEditWindow.close()
                  }
                  else
                  {
                      Qt.createComponent("MessageDisplay.qml").createObject(ausgabeEditWindow, {text:qsTr("Daten nicht korrekt!")})// artikeleditor.visible = true;

                  }
              }


          }
          Button {
              id: cancelButton
              text: qsTr("Cancel")
              DialogButtonBox.buttonRole: DialogButtonBox.DestructiveRole
              onClicked: { ausgabeEditWindow.close()}

          }


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
