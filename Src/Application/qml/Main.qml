import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle {
	anchors.fill: parent
    color: "#CADCDC"

    RowLayout {
        anchors.fill: parent
        anchors.margins: 10

        Button {
            objectName: "button_compile"
            text: "Compile"
        }

        TextField {
            objectName: "textField_parseFilepath"
            placeholderText: "Parse file"

            Layout.fillWidth: true
            Layout.minimumWidth: 0
        }

        TextField {
            objectName: "textField_mockFilepath"
            placeholderText: "Mock file"

            Layout.fillWidth: true
            Layout.minimumWidth: 0
        }

        TextField {
            objectName: "textField_outputFilepath"
            placeholderText: "Output file"

            Layout.fillWidth: true
            Layout.minimumWidth: 0
        }
    }
}
