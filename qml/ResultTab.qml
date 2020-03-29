import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

Pane
{
    id: liveTab
    padding: 0

    RowLayout
    {
        anchors.fill: parent
        spacing: 3

        Item
        {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Pane
            {
                id: liveTablePane
                height: parent.height - 4
                width: parent.width - 4
                anchors.centerIn: parent

                Component{
                        id: columnComponent
                        TableViewColumn{
                            width: 100
                            delegate: nameDelegate
                        }
                    }

                Component{
                    id: nameDelegate
                    Rectangle{
                        anchors.fill: parent
                        color: {
                            if (styleData.selected)
                                return "#9999aa"
                            else
                                return styleData.row % 2 ? "#f8f8f8" : "#FFFFFF"}

                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            color: {
                                if (styleData.selected)
                                    return "white"
                                else
                                    return "black"}
                            font.bold: styleData.selected
                            elide: styleData.elideMode
                            text: styleData.value
                            font.pixelSize: 15
                        }
                    }
                }

                Component{
                    id: header
                    Rectangle{
                        height: 30
                        color: "#eeeeee"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            color: "black"
                            font.bold: true
                            //elide: styleData.elideMode
                            text: styleData.value
                            font.pixelSize: 15
                        }
                    }
                }

                Component{
                    id: rowDelegateTest

                    Rectangle{
                        //anchors.fill: parent
                        height: 30

                        color: {
                            if (styleData.selected)
                                return "#9999aa"
                            else
                                return styleData.alternate ? "#f8f8f8" : "#FFFFFF"}

                    }
                }

                TableView {
                    id: resultView
                    anchors.fill: parent
                    model: demosqlmodel
                    resources:{
                        var roleList = demosqlmodel.userRoleNames
                        var temp = []
                        for (var i in roleList) {
                            var role  = roleList[i]
                            temp.push(columnComponent.createObject(resultView, { "role": role, "title": role}))
                        }
                        return temp
                    }

                    rowDelegate: rowDelegateTest
                    headerDelegate: header
                    selectionMode: SelectionMode.ContiguousSelection
                    backgroundVisible: false
                    sortIndicatorVisible: true
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
                source: liveTablePane
            }
        }

    }

    ListModel
    {

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


            ToolButton {
                icon.source: "img/delete20.png"
                onClicked: {
                    readerModel.deleteReader(index)
                }
            }

        }
    }


}
