import QtQuick 2.15
import QtQuick.Controls 2.12
Item
{
    id: textArea
    height: parent.height
    width: displayRow.width
 //   focus: textDisplay.focus
    property string text:""
    property string iconSource:""
    property string toolTip:""
    property bool readOnly: true
    property int additionToFont: 0
    property int  font_weight: Font.Normal
    property bool hasValidData: true
//   activeFocusOnTab: true;
    signal textWasEdited(var newText)
    signal nextPressed()
    signal previousPressed()
    signal returnPressed()
    signal arrowDownPressed()

    property bool hasFocus: textDisplay.focus

    property int verticalAlignment: Text.AlignVCenter
    property int horizontalAlignment: Text.AlignLeft


    function setFocus(toFocus)
    {
       // textDisplay.setFocus(toFocus);
    }

    Row
    {
      id: displayRow
       height: parent.height
       width: imageDisplay.width + textDisplay.width + seperator.width


       Image
       {
            id: imageDisplay
            height: parent.height*2/3
            width:  source==""?0:height
            anchors.verticalCenter: parent.verticalCenter
            source: textArea.iconSource


       }
        Item
        {
            id: seperator
            height: parent.height
            width: 5
        }

        DisplayText
        {
            id: textDisplay
            height: parent.height
            width: (textDisplay.contentWidth+10)<50?50:textDisplay.contentWidth+10
            text: textArea.text
            readOnly: textArea.readOnly
            focus: textArea.focus
            verticalAlignment: textArea.verticalAlignment
            horizontalAlignment: textArea.horizontalAlignment
            onTextWasEdited:{ textArea.textWasEdited(newText)}
            onNextPressed: {textArea.nextPressed();}
            onPreviousPressed: {textArea.previousPressed();}
            onReturnPressed: {textArea.returnPressed();}
            onArrowDownPressed: {textArea.arrowDownPressed();}


            additionToFont: textArea.additionToFont
            font.weight: textArea.font_weight
            hasValidData: textArea.hasValidData

            onFocusChanged:
            {
                toolTip.showTip = focus;
            }
        }


    }
  /*  MouseArea
    {
       id: mouseArea_Edit
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {toolTip.showTip = true}
        onExited: {toolTip.showTip = false}
        visible: textArea.readOnly
        propagateComposedEvents: true

    }
*/
    ToolTip
    {
      id: toolTip
        text: textArea.toolTip
       delay:200
       property bool showTip: false
       visible: text==""?false:showTip
    }

}
