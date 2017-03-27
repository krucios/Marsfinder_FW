// This is an example Custom Command Qml file. You have full access to the entire Qml language
// for creating any user interface you like. From the ui you can affect the following changes
// with respect to your vehicle:
//    1) Sending COMMAND_LONG commands out over mavlink using QGCButton control
//    2) Modifying parameters
//
// When developing custom Qml file implementations. You must restart QGroundControl to pick up
// the changes. You need to do this even if you select Clear Qml file. Not sure what at the this
// point. Qt must be caching the files somewhere.
// Arguments to CustomCommandWidgetController::sendCommand (Mavlink COMMAND_LONG)
//   command id
//   component id
//   confirmation
//   param 1-7

import QtQuick 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

import QGroundControl.Controls 1.0
import QGroundControl.FactSystem 1.0
import QGroundControl.FactControls 1.0
import QGroundControl.Controllers 1.0

FactPanel {
    id: panel
    
    property var qgcView: null // Temporary hack for broken QGC parameter validation implementation

    CustomCommandWidgetController { id: controller; factPanel: panel }

    // Your own custom changes start here - everything else above is always required

    Column {
        spacing: 5
        focus: true

        property int dir_FB: 0
        property int dir_LR: 0

        Keys.onUpPressed: {
            if (dir_FB < 1) {
                dir_FB = dir_FB + 1
                console.log('Up pressed: ' + dir_FB)
                if (dir_FB) {
                    controller.sendCommand(31010,0, 0, 0, 0, 0, 0, 0, 0, 0) // Forward
                } else {
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }
        }
        Keys.onDownPressed: {
            if (dir_FB > -1) {
                dir_FB = dir_FB - 1
                console.log('Down pressed: ' + dir_FB)
                if (dir_FB == -1) {
                    controller.sendCommand(31010,0, 0, 1, 0, 0, 0, 0, 0, 0) // Backward
                } else {
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }
        Keys.onLeftPressed: {
            if (dir_LR < 1) {
                dir_LR = dir_LR + 1
                console.log('Left pressed: ' + dir_LR)
                if (dir_LR) {
                    controller.sendCommand(31010,0, 0, 2, 0, 0, 0, 0, 0, 0) // Left
                } else {
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }
        Keys.onRightPressed: {
            if (dir_LR > -1) {
                dir_LR = dir_LR - 1
                console.log('Right pressed: ' + dir_LR)
                if (dir_LR == -1) {
                    controller.sendCommand(31010,0, 0, 3, 0, 0, 0, 0, 0, 0) // Right
                } else {
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0) // Stop
                }
            }

        }
        // The QGCButton control is provided by QGroundControl.Controls. It is a wrapper around
        // the standard Qml Button element which using the default QGC font and color palette.

        RowLayout {
            Label {
                text: "Directions"
                color: "white"
            }

            Button {
                text: "FORWARD"
                onClicked: {
                    controller.sendCommand(31010,0, 0, 0, 0, 0, 0, 0, 0, 0)
                }
            }

            Button {
                text: "BACKWARD"
                onClicked: {
                    controller.sendCommand(31010,0, 0, 1, 0, 0, 0, 0, 0, 0)
                }
            }

            Button {
                text: "ROUND_LEFT"
                onClicked: {
                    controller.sendCommand(31010,0, 0, 2, 0, 0, 0, 0, 0, 0)
                }
            }

            Button {
                text: "ROUND_RIGHT"
                onClicked: {
                    controller.sendCommand(31010,0, 0, 3, 0, 0, 0, 0, 0, 0)
                }
            }

            Button {
                text: "STOP"
                onClicked: {
                    controller.sendCommand(31010,0, 0, 4, 0, 0, 0, 0, 0, 0)
                }
            }
        }

//        RowLayout {
//            Label {
//                text: "Motor switch"
//                color: "white"
//            }
//
//            Switch {
//                id: motor_enable
//                checked: false
//                onCheckedChanged: {
//                    controller.sendCommand(31010, 0, 0, checked ? 7 : 0, checked ? 7 : 0, checked ? 7 : 0, checked ? 7 : 0, 0, 0, 0)
//                }
//            }
//        }

//        Button {
//            text: "Calibrate"
//            onClicked: {
//                controller.sendCommand(31012,0, 0, 0, 0, 0, 0, 0, 0, 0)
//            }
//        }
    }
}