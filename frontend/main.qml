import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import QtWebSockets 1.0

Window {
    id: window
    visible: true
    title: qsTr("Hello World")
    property string hostname: "localhost"
    property int port: 8081

    Rectangle {
        color: "#00508c"
        anchors.fill: parent
        ColumnLayout {
            anchors.fill: parent

            Image {
                id: image1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                source: "toradex.png"
            }

            Rectangle {
                id: virtualled
                width: 100
                height: 100
                radius: 50
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                color: "#ff0000"
            }

            RowLayout {
                id: rowLayout
                Button {
                    id: button
                    text: qsTr("ON")
                    Layout.minimumHeight: 100
                    display: AbstractButton.TextBesideIcon
                    Layout.fillWidth: true
                    background: Rectangle {
                        anchors.fill: parent
                        color: parent.pressed ?  "#00dd00" : "#00ff00"
                    }

                    onClicked: {
                        backend.sendTextMessage("enable");
                        virtualled.color = "#00ff00";
                    }
                }

                Button {
                    id: button1
                    text: qsTr("OFF")
                    Layout.minimumHeight: 100
                    display: AbstractButton.TextBesideIcon
                    Layout.fillWidth: true

                    background: Rectangle {
                        anchors.fill: parent
                        color: parent.pressed ?  "#dd0000" : "#ff0000"
                    }

                    onClicked: {
                        backend.sendTextMessage("disable");
                        virtualled.color = "#ff0000";
                    }
                }
            }
        }
    }

    WebSocket {
        id: backend
        url: "ws://" + hostname + ":" + port + "/led/0"
        active: true
        onStatusChanged: {
            if (status === WebSocket.Open ||
                    status === WebSocket.Connecting)
                reconnect.running = false;
            else {
                active = false;
                reconnect.running = true;
            }
        }
    }
    Timer {
        id: reconnect
        interval: 1000; repeat: true
        onTriggered: backend.active = true
    }
}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
