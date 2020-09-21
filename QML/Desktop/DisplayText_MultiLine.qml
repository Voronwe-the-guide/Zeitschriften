//Difference to normal is in up/Down tab
import QtQuick 2.15
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4

TextEdit //Field //Input//Edit
{
    id: textdisplay
    signal nextPressed()
    signal previousPressed()
    signal returnPressed()
    signal textWasEdited(var newText)
    property string oldText;
    property string toolTip:""
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
        anchors.fill: parent
        color: textdisplay.hasValidData? "lightgrey":"red" //"transparent"
        opacity: 0.6
        border.color: parent.focus?"blue":"transparent"
        border.width: 3
        visible:!textdisplay.readOnly//?false : parent.focus
        z: -2
    }
 /*   MouseArea
    {
       id: mouseArea_Edit
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {toolTip.showTip = true}
        onExited: {toolTip.showTip = false}
        visible: textdisplay.readOnly
        propagateComposedEvents: true

    }
*/
    ToolTip
    {
      id: toolTip
        text: textdisplay.toolTip
       delay:200
       property bool showTip: textdisplay.focus
       visible: text==""?false:showTip
    }
 }
