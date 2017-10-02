import QtQuick 2.4
import QtQuick.Controls 2.2
import QtQuick.Controls.Styles 1.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 800
    height:600
    objectName: "rootWindow"
    title: qsTr("CPU Info")

    ListView {
       id :listViewComponent
       width: parent.width
       height: parent.height
       objectName: "cpuInfoList"
       boundsBehavior : Flickable.StopAtBounds
       delegate: Rectangle {
           height: 30
           width: parent.width
           color: "#350820"
           Text {
               height: 30
               width: parent.width
               color : "white"
               text: modelData
               wrapMode: Text.Wrap
            }
       }
   }

}
