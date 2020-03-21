import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.3

Dialog
{
    id: window

    standardButtons: Dialog.Ok | Dialog.Cancel

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


    property string titleText: "Reader"
    property int readerIndex: -1

    function setupForNewReader()
    {
        titleText = "Neuer Reader";
        readerIndex = -1;
        cbReaderType.model = readerModel.readerTypes();
        cbReaderType.currentIndex = -1;
        cbReaderType.enabled = true;
        tfReaderName.clear();
        tfReaderAddress.clear();
        standardButton(Dialog.Ok).enabled = false;
    }

    function setupForReader(i)
    {
        var index = parseInt(i);
        if (index >= 0 && index < readerModel.rowCount())
        {
            titleText = "Reader bearbeiten";
            cbReaderType.model = readerModel.readerTypes();
            cbReaderType.currentIndex = readerModel.data(index, readerModel.roleIndex("readerTypeIndex"));
            cbReaderType.enabled = false;

            tfReaderName.setText(readerModel.data(index, readerModel.roleIndex("readerName")));

            tfReaderAddress.setText(readerModel.data(index, readerModel.roleIndex("readerAddress")));
            readerIndex = index;
        }
    }
    
    function allInputsAreValid()
    {
        //TODO: implement user input validity check
        if (cbReaderType.currentIndex >= 0 && tfReaderName.content != "" && tfReaderAddress.content != "")
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

    title: titleText
    width: 400
    height: 300


    Pane
    {
        id: readerOptionsPane
        width: parent.width - 16
        height: parent.height - 16
        anchors.centerIn: parent

        property int elementWidth: 140

        GridLayout
        {
            anchors.fill: parent
            rows: 2
            columns: 2

            TextFieldWithCaption
            {
                id: tfReaderName
                Layout.fillHeight: true
                Layout.preferredWidth: readerOptionsPane.elementWidth
                title: "Name des Readers"
                placeholder: "Readername"
            }


            Item
            {
                Layout.fillHeight: true
                Layout.preferredWidth: readerOptionsPane.elementWidth
                Text
                {
                    id: lbReaderType
                    text: "Typ"
                }
                ComboBox
                {
                    id: cbReaderType
                    anchors.top: lbReaderType.bottom
                    width: parent.width
                    onActivated: toggleOkButton();
                }
            }




            TextFieldWithCaption
            {
                id: tfReaderAddress
                Layout.fillHeight: true
                Layout.preferredWidth: readerOptionsPane.elementWidth
                title: "IP"
                placeholder: "192.168.0.1"
            }
            TextFieldWithCaption
            {
                id: tfReaderPort
                Layout.fillHeight: true
                Layout.preferredWidth: readerOptionsPane.elementWidth
                title: "Port/COM"
                placeholder: "42"
            }



        }

        /*ColumnLayout
        {
            anchors.fill: parent
            spacing: 2

            Item
            {
                id: name
                Layout.fillWidth: true
                Layout.preferredHeight: 60

                RowLayout
                {
                    anchors.fill: parent
                    spacing: 10


                    TextFieldWithCaption
                    {
                        id: tfReaderName
                        Layout.fillHeight: true
                        Layout.preferredWidth: 160
                        title: "Name des Readers"
                        placeholder: "Readername"
                    }


                    Item
                    {
                        Layout.fillHeight: true
                        Layout.preferredWidth: 160
                        Text
                        {
                            id: lbReaderType
                            text: "Typ"
                        }
                        ComboBox
                        {
                            id: cbReaderType
                            anchors.top: lbReaderType.bottom
                            width: parent.width
                        }
                    }
                }
            }


            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 60

                RowLayout
                {
                    anchors.fill: parent
                    spacing: 10

                    TextFieldWithCaption
                    {
                        id: tfReaderAddress
                        Layout.fillHeight: true
                        Layout.preferredWidth: 160
                        title: "IP"
                        placeholder: "192.168.0.1"
                    }
                    TextFieldWithCaption
                    {
                        id: tfReaderPort
                        Layout.fillHeight: true
                        Layout.preferredWidth: 160
                        title: "Port/COM"
                        placeholder: "42"
                    }
                }
            }
            Item {
                Layout.fillHeight: true
                Layout.fillWidth: true
            }

        }*/

    }

    DropShadow
    {
        id: readerOptionsShadow
        anchors.fill: source
        cached: true
        horizontalOffset: 2
        verticalOffset: 2
        radius:7.0
        samples: 16
        color: "#bbb"
        smooth: true
        source: readerOptionsPane
    }



}
