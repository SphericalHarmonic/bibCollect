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
    }

    function setupForReader(i)
    {
        index = parseInt(i);
        if (index >= 0 && index < readerModel.rowCount())
        {
            tfReaderName.text = readerModel.data(index, readerModel.roleIndex("readerName"));

        }
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

                RowLayout
                {
                    anchors.fill: parent

                    ColumnLayout
                    {
                        Layout.alignment: Qt.AlignTop
                        Layout.preferredWidth: 180
                        Layout.fillHeight: true
                        spacing: 10
                        Item
                        {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50

                            Text
                            {
                                id: lbReaderName
                                text: "Name des Readers"
                            }
                            TextField
                            {
                                id: tfReaderName
                                anchors.top: lbReaderName.bottom
                                placeholderText: "Readername"
                                width: parent.width
                            }
                        }

                        Item
                        {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50
                            Text
                            {
                                id: lbReaderAddress
                                text: "IP"
                            }
                            TextField
                            {
                                id: tfReaderAddress
                                anchors.top: lbReaderAddress.bottom
                                placeholderText: "000.000.000.000"
                                width: parent.width

                                inputMask: "000.000.000.000:0"
                                //validator: RegExpValidator {
                                //    regExp: /^((?:[0-1]?[0-9]?[0-9]|2?[0-4]?[0-9]|25[0-5]).){3}(?:[0-1]?[0-9]?[0-9]|2?[0-4]?[0-9]|25[0-5])$/
                                //}
                            }

                        }
                    }

                    ColumnLayout
                    {
                        Layout.alignment: Qt.AlignTop
                        Layout.preferredWidth: 180
                        Layout.fillHeight: true
                        Item
                        {
                            Layout.fillWidth: true
                            Layout.preferredHeight: 50
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
                            readerModel.addReader(cbReaderType.currentIndex, tfReaderName.text, tfReaderAddress.text);
                            window.close();
                        }
                    }
                }
            }
        }
    }
}
