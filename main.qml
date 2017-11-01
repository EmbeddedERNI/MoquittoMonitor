import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QMQTT 1.0
import Qt.labs.settings 1.0


ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Mosquitto trafic monitor")


    MQTTClient{
        id: mqtt
        hostip: hostip.text
        //         property int ids: 0
        subscribeTopic: subscribed.text

        onNewMessage: {
            console.log("Message with topic " + topic + "; " + message)
            var now = new Date();
            var timestamp = now.toLocaleTimeString()
            var alreadyExist = false
            for (var x =0; x < messageList.count; x++){
                if(messageList.get(x).topic === topic){
                    messageList.setProperty(x,"message", message)
                    messageList.setProperty(x,"updateTime",timestamp)
                    if (order.checked){
                        messageList.move(x,0,1)
                    }
                    alreadyExist = true
                    break;
                }
            }
            if (!alreadyExist){
                messageList.append({"topic":topic,"message":message ,"updateTime": timestamp})
                if (order.checked){
                    messageList.move(messageList.count-1,0,1)
                }
            }
        }

    }

    ListModel{
        id: messageList
        ListElement{
            topic:"Tpo2"
            message:"Hi3"
            updateTime: "00:00"
        }

        ListElement{
            topic:"Tpo"
            message:"Hi"
            updateTime: "00:00"
        }
        Component.onCompleted: messageList.clear()
    }

    Settings {
        property alias hostip_value: hostip.text
        property alias subscribetopic_value: subscribed.text

        property alias sendtopic_value: topic.text
        property alias sendmessage_value: message.text

    }
    GridLayout{
        anchors.rightMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.topMargin: 10
        anchors.fill: parent
        anchors.margins: 10
        columns: 5
        Image{
            id: fill
            height: 100
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            fillMode: Image.PreserveAspectFit

            source: "http://www.itnove.com/sites/default/files/erni.png"
            //            scale: 1.1
            Layout.rowSpan: 3
            Layout.column: 4
            Layout.fillWidth: true

        }
        Text {
            id: text1
            Layout.column: 0
            Layout.row: 0
            text: qsTr("MQTT Information")
            Layout.fillWidth: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.columnSpan: 3
            font.pixelSize: 32
        }
        Rectangle{
            Layout.column: 0
            Layout.row: 1
            width: hostip.height
            height: hostip.height
            radius: width
            color: mqtt.isConnected? "green": "red"
        }
        TextField{
            Layout.column: 1
            Layout.row: 1
            id: hostip
            placeholderText: "Host ip"
            text: "192.168.0.164"
        }
        TextField{
            Layout.column: 2
            Layout.row: 1
            id: subscribed
            placeholderText: "Subscribed topic"
            text: "/#"
        }
        TextField{
            Layout.column: 1
            Layout.row: 2
            id: topic
            placeholderText: "Topic"

        }
        TextField{
            Layout.column: 2
            Layout.row: 2
            id: message
            placeholderText: "Message"
            //                text: "192.168.0.164"
        }
        Button{
            Layout.column: 3
            Layout.row: 2
            text: "Send"
            onClicked: {
                mqtt.publishMsg(0,topic.text, message.text)
            }
        }
        CheckBox{
            id: order
            Layout.column: 3
            Layout.row: 1
            text: "Order by update"
        }

        Frame{
            Layout.fillWidth: true
            Layout.columnSpan: 5
            Layout.column: 0
            Layout.row: 3
            Layout.fillHeight:true
            TableView {
                clip: true
                anchors.fill: parent
                //                Repeater{
                //                    model: messageList
                //                    Row{
                //                        Text {
                //                            text: "Topic "
                //                        }
                //                        Text{
                //                            width: 100
                //                            text: model.topic
                //                        }
                //                        Text {
                //                            text: " Message "
                //                        }
                //                        Text {
                //                            width: 100
                //                            text: model.message
                //                        }
                //                    }
                //                }
                contentModel: messageList
            }
        }

    }
}

