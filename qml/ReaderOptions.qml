import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.3

Window
{
    id: window

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
        if (cbReaderType.currentIndex >= 0)
            return true
        else
            return false;
    }

    Material.theme: Material.Light
    Material.accent: Material.DeepOrange

    title: titleText
    width: 400
    height: 400

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 0

        Item
        {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Pane
            {
                id: readerOptionsPane
                width: parent.width - 16
                height: parent.height - 16
                anchors.centerIn: parent

                ColumnLayout
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

                }

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
        Item
        {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            // padding: 0
            RowLayout
            {
                Layout.margins: 10
                anchors.fill: parent
                Item
                {
                    Layout.fillWidth: true;
                    Layout.preferredHeight: 20
                }

                Button
                {
                    text: "Abbrechen"
                    icon.source: "img/delete20.png"
                    flat: true

                    onClicked:
                    {
                        window.close();
                    }
                }
                Button
                {
                    text: "Ok"
                    icon.source: "img/ok20.png"
                    flat: true

                    onClicked:
                    {
                        if (readerIndex < 0)
                        {
                            readerModel.addReader(cbReaderType.currentIndex, tfReaderName.content, tfReaderAddress.content);
                            window.close();
                        }
                        else
                        {
                            if (allInputsAreValid())
                            {
                                readerModel.setIp(readerIndex, tfReaderAddress.content + ':' + tfReaderPort.content);
                                readerModel.setName(readerIndex, tfReaderName.content);
                                window.close();
                            }
                        }
                    }
                }
                Item
                {
                    Layout.preferredWidth: 10;
                    Layout.preferredHeight: 20
                }
            }
        }
    }
}
