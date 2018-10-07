import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import QtQuick.Window 2.11
import QtQuick.Controls.Material 2.3

Window
{
    property string titleText: "Reader"

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

                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        ColumnLayout
                        {
                            Item
                            {
                                Layout.fillWidth: true
                                Text
                                {
                                    id: lbReaderName
                                    text: "Name des Readers"
                                }
                                TextField
                                {
                                    anchors.top: lbReaderName.bottom
                                    placeholderText: "Readername"
                                    width: parent.width
                                }

                            }
                        }
                    }
                    Item
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
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
                }
                Button
                {
                    text: "Ok"
                    icon.source: "img/ok20.png"
                    flat: true
                }
            }
        }
    }
}
