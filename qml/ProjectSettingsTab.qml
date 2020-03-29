import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Pane
{
    id: projectSettingsTab
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
                id: buttonsPane
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
                        text: "Buttons"
                        font.pixelSize: 14
                    }
                    Button {
                        text: "Event laden"
                        flat: true
                    }
                    Button {
                        text: "Letztes Event..."
                        flat: true
                    }
                    Button {
                        text: "Vorlage laden"
                        flat: true
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Noch ein Button"
                        flat: true
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
                source: buttonsPane
            }
        }
    }


}
