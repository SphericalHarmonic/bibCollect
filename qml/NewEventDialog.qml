import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.3

Dialog
{
    id: window

    //x: (parent.width - width) /2
    //y: (parent.heigh - height) /2

    standardButtons: Dialog.Ok | Dialog.Cancel
    focus: true

    onAccepted: {
        if (readerIndex < 0)        {
            readerModel.addReader(cbReaderType.currentIndex, tfReaderName.content, tfReaderAddress.content);
            window.close();
        }
        else {
            if (allInputsAreValid()) {
                readerModel.setIp(readerIndex, tfReaderAddress.content + ':' + tfReaderPort.content);
                readerModel.setName(readerIndex, tfReaderName.content);
                window.close();
            }
        }
    }
    onRejected: window.close();



    
    function allInputsAreValid()
    {
        //TODO: implement user input validity check
        if (tfEventName.content != "")
            return true
        else
            return false;
    }

    function toggleOkButton()
    {
        if (allInputsAreValid())
            standardButton(Dialog.Ok).enabled = true;
        else
            standardButton(Dialog.Ok).enabled = false;
    }

    Material.theme: Material.Light
    Material.accent: Material.DeepOrange

    title: "Neues Event anlegen"
    width: 400
    height: 300


    Pane {
        id: eventOptionsPane
        width: parent.width - 6
        height: parent.height - 6
        anchors.centerIn: parent

        property int elementWidth: 140

        GridLayout {
            anchors.fill: parent
            rows: 2
            columns: 2

            TextFieldWithCaption {
                id: tfEventName
                Layout.fillHeight: true
                Layout.preferredWidth: eventOptionsPane.elementWidth
                title: "Name des Events"
                placeholder: "Eventname"

                Connections {
                    target: tfEventName.textField
                    onTextChanged: {
                        toggleOkButton()
                    }
                }

                Keys.onPressed: if (event.key === Qt.Key_Return) {
                                   if (allInputsAreValid())
                                       accept()
                                }
            }

            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

            RadioButton {
                text: "Feste Rundenzahl"
                checked: true

            }

            RadioButton {
                text: "Rundenzählung"
            }
        }
    }

    DropShadow
    {
        anchors.fill: source
        cached: true
        horizontalOffset: 2
        verticalOffset: 2
        radius:7.0
        samples: 16
        color: "#bbb"
        smooth: true
        source: eventOptionsPane
    }
}
