import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

import led 1.0

Window {
    id: window
    width: 480
    height: 800
    visible: true
    title: qsTr("Hello World")

    Led {
        property bool isEnabled: false
        id: led
        onIsEnabledChanged: isEnabled ? enable() : disable()
    }

    Rectangle {
        color: "#FFFFFF"
        anchors.fill: parent
        ColumnLayout {
            anchors.fill: parent

            Image {
                id: image1
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                source: "embear.png"
            }

            Rectangle {
                id: virtualled
                width: 100
                height: 100
                radius: 50
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                color: "#474947"

                states: State {
                    name: "on"; when: led.isEnabled
                    PropertyChanges { target: virtualled; color: "#C57452" }
                }

                transitions: Transition {
                    ColorAnimation { duration: 1000 }
                }
            }

            RowLayout {
                id: rowLayout
                Button {
                    id: onButton
                    text: qsTr("ON")
                    Layout.minimumHeight: 100
                    display: AbstractButton.TextBesideIcon
                    Layout.fillWidth: true
                    background: Rectangle {
                        id: onButtonColor
                        anchors.fill: parent
                        color: "#C57452"

                        states: State {
                            name: "pressed"; when: onButton.pressed
                            PropertyChanges { target: onButtonColor; color: "#D58462" }
                        }

                        transitions: Transition {
                            ColorAnimation { duration: 200 }
                        }
                    }

                    onClicked: {
                        led.isEnabled = true
                    }
                }

                Button {
                    id: offButton
                    text: qsTr("OFF")
                    Layout.minimumHeight: 100
                    display: AbstractButton.TextBesideIcon
                    Layout.fillWidth: true

                    background: Rectangle {
                        id: offButtonColor
                        anchors.fill: parent
                        color: "#474947"

                        states: State {
                            name: "pressed"; when: offButton.pressed
                            PropertyChanges { target: offButtonColor; color: "#373937" }
                        }

                        transitions: Transition {
                            ColorAnimation { duration: 200 }
                        }

                    }

                    onClicked: {
                        led.isEnabled = false
                    }
                }
            }
        }
    }
}
