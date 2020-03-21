import QtQuick 2.7
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0
import QtQuick.Controls.Material 2.3


ApplicationWindow
{

    Material.theme: Material.Light
    Material.accent: Material.DeepOrange

    visible: true
    width: 1280
    height: 800
    title: qsTr("bibCollect")
    property int margin: 7

    Pane
    {
        id: applicationBackground
        anchors.fill: parent

        ColumnLayout
        {
            id: mainWindowLayout
            anchors.fill: parent
            anchors.margins: margin

            Item
            {

                Layout.fillWidth: true
                Layout.preferredHeight: 200
                Pane
                {
                    id: topWidgetBar
                    height: parent.height - 4
                    width: parent.width - 4
                    anchors.centerIn: parent
                    //anchors.fill: parent

                    RowLayout
                    {
                        anchors.fill: parent
                        anchors.margins: margin

                        GroupBox {
                            id: readerInfoBox
                            title: "Reader"
                            font.pixelSize: 14
                            font.bold: true
                            Layout.fillHeight: true
                            Layout.preferredWidth: 200

                            ListView
                            {
                                model: readerModel
                                delegate: readerQuickInfo
                            }
                        }

                        GroupBox {
                            id: hardwareInfoBox
                            title: "sonstiges"
                            font.pixelSize: 14
                            font.bold: true
                            Layout.fillHeight: true
                            Layout.preferredWidth: 150
                            Label {
                                text: "status"
                                anchors.centerIn: parent
                                anchors.horizontalCenter: parent.Center
                            }
                        }
                        GroupBox {
                            id: challengeInfoBox
                            title: "Challenges"
                            font.pixelSize: 14
                            font.bold: true
                            Layout.fillHeight: true
                            Layout.preferredWidth: 150
                            Label {
                                text: "status"
                                anchors.centerIn: parent
                                anchors.horizontalCenter: parent.Center
                            }
                        }
                        GroupBox {
                            id: rectentTagsBox
                            title: "Einlaufliste"
                            font.pixelSize: 14
                            font.bold: true
                            Layout.fillHeight: true
                            Layout.fillWidth: true

                            Label {
                                text: "Liste"
                                anchors.centerIn: parent
                                anchors.horizontalCenter: parent.Center
                            }
                        }
                        ClockWidget
                        {
                            id: mainClockInfoBox
                            Layout.fillHeight: true
                        }
                    }
                }

                DropShadow
                {
                    id: topWidgetBarShadow
                    anchors.fill: source
                    cached: true
                    horizontalOffset: 2
                    verticalOffset: 2
                    radius:7.0
                    samples: 16
                    color: "#bbb"
                    smooth: true
                    source: topWidgetBar
                }
            }

            Item
            {
                Layout.fillHeight: true
                Layout.fillWidth: true
                MainTabView {
                    id: mainTabView
                    height: parent.height - 4
                    width: parent.width - 4
                    anchors.centerIn: parent
                }
                DropShadow
                {
                    id: mainRectShadow
                    anchors.fill: source
                    cached: true
                    horizontalOffset: 2
                    verticalOffset: 2
                    radius:7.0
                    samples: 16
                    color: "#bbb"
                    smooth: true
                    source: mainTabView
                }
            }
        }
    }

    footer: Pane
    {
        id: bottomInfoBar
        height:  35
        Material.background: "#eee"
        RowLayout
        {
            anchors.fill: parent
            Rectangle
            {
                //text: "Projektname"
                color: "orange"
                //font.bold: true
                Layout.fillWidth: true
                Layout.preferredHeight: 10
                Layout.alignment: Qt.AlignVCenter
            }
            Label
            {
                text: "Projektname"
                //color: "orange"
                font.bold: true
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignVCenter
            }
            Label
            {
                text: "Sonntag, 10. November 2018"
                //color: "orange"
                font.bold: true
                Layout.preferredWidth: 220
            }
            Label
            {
                text: "10:23:08"
                //color: "orange"
                font.bold: true
                Layout.preferredWidth: 100
            }
            Label
            {
                text: "192.169.1.1:23"
                //color: "orange"
                font.bold: true
                Layout.preferredWidth: 120
            }
        }
    }


    Component
    {
        id: readerQuickInfo
        Rectangle
        {
            id: quickInfoBackground
            width: parent.width
            height: 40
            color: "#aaa"

            radius: 2
            border.width: 2
            border.color: "grey"

            RowLayout
            {
                anchors.fill: parent

                Rectangle
                {
                    width: 33
                    height: 33
                    color:
                    { if (readerState === 0)
                        { return "#F44336" ; }
                        else if (readerState === 1)
                        { return "#2196F3" ; }
                        else
                        { return "#4CAF50" ; }
                    }
                    radius: 8
                    border.width: 3
                    border.color: "#fff"

                    Image
                    {
                        anchors.fill: parent
                        anchors.margins: 6
                        source:
                        {
                            if (readerState === 0)
                            { return "img/circle_unchecked_20.png"; }
                            else if (readerState === 1)
                            { return "img/circle_checked_20.png"; }
                            else
                            { return "img/circle_checked_20.png"; }
                        }

                    }
                }

                ColumnLayout
                {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Text {
                        text: readerName
                        font.bold: true
                    }
                    Text { text: readerAddress  }
                }


                ToolButton
                {
                    icon.source:
                    {
                        if (readerState === 2)
                        { return "img/stop.png"; }
                        else
                        { return "img/play48.png"; }
                    }
                    onClicked:
                    {
                        if (readerState === 1)
                        { readerModel.startReader(index); }
                        else if (readerState === 2)
                        { readerModel.stopReader(index); }
                    }
                }

            }




            //Item { Layout.fillWidth: true; Layout.preferredHeight: 40; Rectangle { anchors.fill: parent; color: "red" }}


        }
    }

}
