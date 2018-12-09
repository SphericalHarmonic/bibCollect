import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Pane
{
    id: hardwareTab
    padding: 0

    RowLayout
    {
        anchors.fill: parent
        spacing: 3

        Item
        {
            Layout.fillHeight: true
            Layout.preferredWidth: 350
            Pane
            {
                id: readerListPane
                height: parent.height - 4
                width: parent.width - 4
                anchors.centerIn: parent


                ColumnLayout
                {
                    anchors.fill: parent
                    spacing: 5
                    Text
                    {
                        Layout.preferredHeight: 30
                        Layout.fillWidth: true
                        text: "Verfügbare Reader"
                        font.pixelSize: 14
                    }
                    Pane
                    {
                        padding:0
                        id: readerList
                        Layout.fillHeight: true
                        Layout.preferredHeight: 300
                        Layout.rightMargin: 5
                        ListView
                        {
                            id: readerView
                            anchors.fill: parent
                            model: readerModel//readerTestModel
                            delegate: readerDelegate
                        }
                    }
                    Pane
                    {
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true

                        Button
                        {
                            flat: true
                            text: "Neuer Reader"
                            icon.source: "img/add20.png"

                            onClicked:
                            {
                                readerOptions.setupForNewReader();
                                readerOptions.show();
                            }
                        }
                    }
                    Pane
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                    }

                }

            }
            DropShadow
            {
                id: topWidgetBarShadow
                anchors.fill: source
                cached: true
                horizontalOffset: 1
                verticalOffset: 1
                radius:6.0
                samples: 16
                color: "#ccc"
                smooth: true
                source: readerListPane
            }
        }

    }

    ListModel
    {
        id: readerTestModel
        ListElement
        {
            readerName: "UHF1"
            readerType: "UHF"
            readerState: 0
            readerAdress: "192.168.1.4"
            batteryCharge: 78
            tagCount: 0
            gatingMode: 0
            timingMode: 0
            inUse: true
        }
        ListElement
        {
            readerName: "Backup2"
            readerType: "UHF"
            readerState: 0
            readerAdress: "192.168.1.5"
            batteryCharge: 100
            tagCount: 473
            gatingMode: 0
            timingMode: 0
            inUse: false
        }
    }

    Component
    {
        id: readerDelegate
        RowLayout
        {
            width: parent.width
            height: 40
            spacing: 5
            CheckBox
            {
                checked: inUse
            }
            Text {
                text: readerName
                font.bold: true
            }
            Text { text: readerType }
            Text { text: readerAddress;  }
            Item { Layout.fillWidth: true; Layout.preferredHeight: 40; Rectangle { anchors.fill: parent; color: "red" }}

            ToolButton
            {
                icon.source: "img/edit20.png"

                onClicked:
                {
                    readerOptions.setupForReader(index);
                    readerOptions.show();
                }
            }


            ToolButton {icon.source: "img/delete20.png"}

        }
    }

    ReaderOptions
    {
        id: readerOptions
        //visible: false;
    }

}
