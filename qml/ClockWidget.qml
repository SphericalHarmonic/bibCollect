import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

Pane {

    property string displayTime

    Timer {
        interval: 100; running: true; repeat: true;
        onTriggered: mainClockInfoBox.timeChanged();
    }

    function timeChanged() {
        timeDisplay.text = new Date().toLocaleTimeString(Qt.locale("de_DE"),"hh:mm:ss") + ".5" ;
    }
    ColumnLayout
    {
        anchors.fill: parent
        Rectangle
        {
            Layout.minimumWidth: 280
            Layout.preferredHeight: 70
            color: "black"
            Label {
                id: timeDisplay
                //text: displayTime + ".5"
                font.pixelSize: 50
                font.family: "Consolas"
                color: "orange"

                anchors.centerIn: parent
            }
        }

        RowLayout
        {
            spacing: 0
            Layout.fillHeight: true

            ComboBox {
                Layout.preferredWidth: 115
                Layout.preferredHeight: 40
                antialiasing: true
                font.pixelSize: 12
                model: [ "Uhrzeit", "Welle 1", "Welle 2" ]
            }
            Switch {
                id: ledSyncSwitch

                text: ""
                antialiasing: true
                rightPadding: 2
                leftPadding: 2
                topPadding: 4
                padding: 8
                font.pixelSize: 9

            }

            ComboBox {
                Layout.preferredWidth: 115
                Layout.preferredHeight: 40
                antialiasing: true
                font.pixelSize: 12
                model: [ "Uhrzeit", "Welle 1", "Welle 2" ]
            }



        }
    }
}
