import QtQuick 2.7
import QtQuick.Controls 2.0

ListView {
       id: listView
       anchors.fill: parent

       contentWidth: headerItem.width
       flickableDirection: Flickable.VerticalFlick

       property var headerModel: ["Topic", "Message", "UpdateTime"]
       property alias contentModel: listView.model

       headerPositioning: ListView.OverlayHeader
       delegate: Column {
           id: delegate
           property int row: index
           width: listView.width

           Row {
               spacing: 1
                   ItemDelegate {
                       width: listView.headerItem.itemAt(1).width
                       text: topic
                   }
                   ItemDelegate {
                       width: listView.headerItem.itemAt(2).width
                       text: message
                   }
                   ItemDelegate {
                       width: listView.headerItem.itemAt(3).width
                       text: updateTime
                   }
           }
           Rectangle {
               color: "silver"
               width: parent.width
               height: 1
           }
       }

       ScrollIndicator.horizontal: ScrollIndicator { }
       ScrollIndicator.vertical: ScrollIndicator { }

       header: Row {
           z:2
           spacing: 1
           function itemAt(index) { return repeater.itemAt(index) }
           Repeater {
               id: repeater
               model: listView.headerModel
               Label {
                   width: listView.width/3
                   text: modelData
                   font.bold: true
                   font.pixelSize: 20
                   padding: 10
                   background: Rectangle { color: "silver" }
               }
           }
       }

   }
