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
            Layout.preferredWidth: 200
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
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Letztes Event..."
                        flat: true
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Vorlage laden"
                        flat: true
                        Layout.fillWidth: true
                    }
                    Item {
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Button {
                        text: "Noch ein Button"
                        flat: true
                        Layout.fillWidth: true
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

        Item
        {
            Layout.fillHeight: true
            //Layout.preferredWidth: 400
            Layout.fillWidth: true
            Pane
            {
                id: projectOptionsPane
                height: parent.height - 4
                width: parent.width - 4
                anchors.centerIn: parent

                GridLayout
                {
                    anchors.fill: parent
                    columns: 2

                    TextFieldWithCaption {
                        id: tfEventName
                        //Layout.fillHeight: true
                        Layout.preferredWidth: 250
                        title: "Name des Wettkampfes"
                        placeholder: "Name"

                        /*Connections {
                            target: tfReaderName.textField
                            onTextChanged: {
                                toggleOkButton()
                            }
                        }*/

                        Keys.onPressed: if (event.key === Qt.Key_Return) {
                                           if (allInputsAreValid())
                                               accept()
                                        }
                    }
                }
            }
            DropShadow
            {
                id: projectOptionsShadow
                anchors.fill: source
                cached: true
                horizontalOffset: 1
                verticalOffset: 1
                radius:6.0
                samples: 16
                color: "#ccc"
                smooth: true
                source: projectOptionsPane
            }
        }
    }
}
