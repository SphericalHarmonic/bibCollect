import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0

Item
{
    property string title: ""
    property string placeholder: ""
    property string content: textfield.text
    function clear()
    {
        textfield.clear()
    }
    function setText(text)
    {
        textfield.text = text
    }

    Text
    {
        id: caption
        text: title
    }
    TextField
    {
        id: textfield
        anchors.top: caption.bottom
        placeholderText: placeholder
        width: parent.width
        selectByMouse: true
    }
}
