import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Pane
{
    //color: "#222"
    //anchors.fill: parent

    ColumnLayout
    {
        id: tabViewLayout
        anchors.fill: parent
        //spacing: 10

        TabBar
        {
            id: tabBar
            //Layout.preferredHeight: 30
            //Layout.fillWidth: true
            contentHeight: 35

            TabButton
            {
                text: qsTr("Projekt")
                width: 90


                ColorAnimation
                {
                    from: "white"
                    to: "black"
                    duration: 200
                }
            }
            TabButton
            {
                text: qsTr("Wettkampf")
                width: 120
            }
            TabButton
            {
                text: qsTr("Tags")
                width: 60
            }
            TabButton
            {
                text: qsTr("Teilnehmer")
                width: 120
            }
            TabButton
            {
                text: qsTr("Hardware")
                width: 110
            }
            TabButton
            {
                text: qsTr("Live")
                width: 70
            }
            TabButton
            {
                text: qsTr("Ergebnisse")
                width: 120
            }
            TabButton
            {
                text: qsTr("Optionen")
                width: 110
            }
            TabButton
            {
                text: qsTr("Log")
                width: 60
            }
        }

        StackLayout {
            currentIndex: tabBar.currentIndex
            Layout.fillHeight: true
            Layout.fillWidth: true


            ProjectSettingsTab {
                Label {
                    text: qsTr("Projekteinstellungen")
                    anchors.centerIn: parent
                }
            }

            Item {
                Label {
                    text: qsTr("Wettkampfoptionen")
                    anchors.centerIn: parent
                }
            }
            Item {
                Label {
                    text: qsTr("Startnummern")
                    anchors.centerIn: parent
                }
            }
            Item {
                Label {
                    text: qsTr("Teilnehmer")
                    anchors.centerIn: parent
                }
            }
            HardwareTab {
                Label {
                    text: qsTr("Hardwareeinstellungen")
                    anchors.centerIn: parent
                }
            }
            Item {
                Label {
                    text: qsTr("Live-Ansicht")
                    anchors.centerIn: parent
                }
            }
            ResultTab {

            }
            Item {
                Label {
                    text: qsTr("Einstellungen")
                    anchors.centerIn: parent
                }
            }
            Item {
                Label {
                    text: qsTr("Log")
                    anchors.centerIn: parent
                }
            }
        }
    }
}
