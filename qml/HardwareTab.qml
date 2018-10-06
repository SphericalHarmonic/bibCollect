import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Pane
{
    id: hardwareTab


    RowLayout
    {
        anchors.fill: parent
        spacing: 5

        Item
        {
            Layout.fillHeight: true
            Layout.preferredWidth: 300
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
                    }
                    Pane
                    {
                        id: readerList
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Layout.rightMargin: 5
                        ListView
                        {
                            id: readerView
                            anchors.fill: parent
                            model: readerTestModel
                            delegate: readerDelegate
                        }
                    }
                    Rectangle
                    {
                        Layout.preferredHeight: 50
                        Layout.fillWidth: true
                        color: "#333"
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
            readerName: "Backup"
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
            Text { text: readerAdress }
            ToolButton {icon.source: "img/edit20.png"}
            ToolButton {icon.source: "img/delete20.png"}

        }
    }

}
