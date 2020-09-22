import QtQuick 2.0

Rectangle
{
    id: rubrikDisplay

    property QtObject listModel
    property int elementCount: rubrikList.count
    width: 150
    height: 150
    border.color: "black"
   // anchors.top: parent.bottom
    function setFocus(isFocus)
    {
        rubrikList.focus = isFocus
    }

    property bool hasFocus: rubrikList.focus
    signal jumpedOut()
    signal textSelected(var text)
 //   z: 10
 //   visible: (!artikelDisplay.readOnlyMode) && (rubrikArea.hasFocus || rubrikList.focus)

    Component
    {
        id: rubrikCompent
        Item
        {
            width: rubrikDisplay.width
            height: rubrikArea.height
            Text
            {
                id: rubrikText
                anchors.fill: parent
                text: model.element
                font.pixelSize:18
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {

                    rubrikDisplay.textSelected(model.element)
                    console.log("text on Muose:"+model.element)
                    //rubrikArea.text = rubrikText.text;
                    rubrikList.currentIndex = model.index;
                    //rubrikArea.focus = true;
                  //  artikelDisplay.rubrikEdit(rubrikArea.text);
                }

            }
        }
    }

    ListView
    {
        id: rubrikList
        anchors.fill: parent
        model: rubrikDisplay.listModel //cRubrikList
        delegate: rubrikCompent
        focus: rubrikDisplay.focus
        clip: true
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        Keys.onEscapePressed: rubrikDisplay.jumpedOut()
        Keys.onUpPressed:
        {
            if (rubrikList.currentIndex == 0)
            {
                //rubrikArea.focus = true;
                rubrikDisplay.jumpedOut()
            }
            else
            {
                rubrikList.currentIndex --;
            }
        }
        Keys.onReturnPressed:
        {
           // console.log("Enter pressed");
            //rubrikDisplay.textSelected(rubrikText.text)

            rubrikDisplay.textSelected(listModel.getElementFromDisplay(rubrikList.currentIndex));
           //  rubrikArea.focus = true;
           //  artikelDisplay.rubrikEdit(rubrikArea.text);
        }

        onCountChanged:
        {
            rubrikList.currentIndex =0;
        }


    }
}

