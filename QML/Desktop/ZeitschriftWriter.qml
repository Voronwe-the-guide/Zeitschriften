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

    title: "Edit Zeitschrift"
    flags:  Qt.Window | Qt.WindowSystemMenuHint
            | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowCloseButtonHint
     |Qt.WindowCancelButtonHint
            | Qt.WindowMaximizeButtonHint// | Qt.WindowStaysOnTopHint
    Image
    {
        id: zeitschriftLogo
        width: 100
        height: 100
        source:  cZeitschriftEditor.logoAdress
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                fileDialog.visible = true
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
         id: fileDialog
         title: qsTr("Zeitschriften Logo")
         folder: cZeitschriftEditor.logoAdress // shortcuts.home
         selectMultiple: false
         onAccepted: {
             console.log("Adress of Image: "+fileDialog.fileUrl.toString())
             cZeitschriftEditor.setLogoAdress(fileDialog.fileUrl.toString())
             visible: false;
         }
         onRejected: {
            visible: false
         }
     }



}
