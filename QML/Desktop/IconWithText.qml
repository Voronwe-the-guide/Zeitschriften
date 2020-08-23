import QtQuick 2.0
import QtQuick.Controls 2.12
Item
{
    id: textArea
    height: parent.height
    width: displayRow.width
    property string text:""
    property string iconSource:""
    property string toolTip:""
//   property string fontSize: textDisplay.font.pixelSize
    Tracer {bc: "blue"}
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
            Tracer{}
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
            width: textDisplay.contentWidth+10
            text: textArea.text
        }
    }
    MouseArea
    {
       id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onEntered: {toolTip.showTip = true}
        onExited: {toolTip.showTip = false}


     //   ToolTip.visible: entered
     //   ToolTip.text: "test"
     //   ToolTip.delay: 200
    }
    ToolTip
    {
      id: toolTip
        text: textArea.toolTip
       delay:200
       property bool showTip: false
       visible: text==""?false:showTip


    }

}
