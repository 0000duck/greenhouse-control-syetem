import QtQuick 2.0
import com.mycompany.qmlcomponents 1.0

Rectangle {
    id: root

    width: myWidth
    height: myWidth*3    

    Rectangle {
        id: onButton

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: offButton.top
        color: "gray"

        width: 100
        height: (parent.height-2)/3

        Text {
             anchors.centerIn: parent
             textFormat: Text.RichText
             text:"ON"
             color: "lightsteelblue"
             width: parent.width
             wrapMode: Text.WordWrap
             horizontalAlignment: Text.AlignHCenter
             font { family: "Times"; pixelSize: 30; capitalization: Font.AllUppercase }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.state = "on";
                mySwitchItem.getisOn();
            }
        }
    }

    Rectangle {
        id: offButton

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: onButton.bottom

        color: "gray"

        width:100
        height: (parent.height-2)/3

        Text {
            anchors.centerIn: parent
            textFormat: Text.RichText
            text:"OFF"
            color: "lightsteelblue"
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font { family: "Times"; pixelSize: 30; capitalization: Font.AllUppercase }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                root.state = "off";
                mySwitchItem.getisOn();
            }
        }
    }

    Rectangle{
        id:splitter
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: offButton.bottom
        width:parent.width
        height:3
        color: "black"
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mySwitchItem.getisOn();
            }
        }
     }
    Rectangle{
        id: textLabel
        property alias text: labelText.text
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        color: "#0055ff"

        width:100
        height:(parent.height-2)/3

        Text {
            id:labelText
            anchors.centerIn: parent
            textFormat: Text.RichText
            text: myText
            color: "lightsteelblue"
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter
            font { family: "Times"; pixelSize: 14; capitalization: Font.AllUppercase }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                mySwitchItem.getisOn();
            }
        }
    }

    state: "off"

    states: [
        State {
            name: "on"
            PropertyChanges { target: onButton; color: "green"; }
            PropertyChanges { target: mySwitchItem;isOn:true; }
        },
        State {
            name: "off"
            PropertyChanges { target: offButton; color: "green"; }
            PropertyChanges { target: mySwitchItem; isOn: false; }
        }
       ]

    Slider {
        id:mySwitchItem;
    }

}





