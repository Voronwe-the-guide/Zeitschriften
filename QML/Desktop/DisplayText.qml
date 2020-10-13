import QtQuick 2.15
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TextEdit //Field //Input//Edit
{
    id: textdisplay
    signal nextPressed()
    signal previousPressed()
    signal returnPressed()
    signal arrowDownPressed()

    signal textWasEdited(var newText)
    property string oldText;
    property int additionToFont: 0
    property string textToDisplay:""
    font.pixelSize: 15 + additionToFont
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
    inputMethodHints: Qt.ImhNoPredictiveText
   textFormat: TextEdit.AutoText //Text.StyledText
   wrapMode: Text.NoWrap
    readOnly: true
    selectByMouse: true
    property bool hasValidData: true

     function setFocus(toFocus)
    {
        textdisplay.focus = toFocus;
    }
     textMargin: 0



   KeyNavigation.priority: KeyNavigation.BeforeItem

   Keys.onTabPressed:
   {
         textdisplay.nextPressed();
   }
   Keys.onBacktabPressed:
   {
        textdisplay.previousPressed();

   }

   Keys.onReturnPressed:
   {
       textdisplay.returnPressed();
        textdisplay.nextPressed();

   }
   Keys.onDownPressed:
   {
      textDisplay.arrowDownPressed();
   }

   onTextChanged:
    {
        if (focus)
        {
            textWasEdited(text);
        //    console.log("Send Text edit");
        }
    }

    Rectangle
    {
       // anchors.fill: parent
        width: parent.width+    6
        height: parent.height+6
        anchors.centerIn: parent
        color: textdisplay.hasValidData? "lightgrey":"red" //"transparent"
        opacity: 0.6
        border.color: parent.focus?"blue":"transparent"
        border.width: 3
        visible:!readOnly//?false : parent.focus
        z: -2
    }
 }



