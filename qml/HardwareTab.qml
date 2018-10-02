import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: hardwareTab

    color: "#222"

    RowLayout
    {
        anchors.fill: parent
        spacing: 5

        Rectangle
        {
            color: "#333"
            Layout.fillHeight: true
            Layout.preferredWidth: 300


            ColumnLayout
            {
                anchors.fill: parent
                spacing: 5
                Rectangle
                {
                    Layout.preferredHeight: 30
                    Layout.fillWidth: true
                    color: "#333"
                }
                Rectangle
                {
                    id: readerList
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.rightMargin: 5
                    color: "#222"
                }
                Rectangle
                {
                    Layout.preferredHeight: 250
                    Layout.fillWidth: true
                    color: "#333"
                }

            }

        }


    }

}
