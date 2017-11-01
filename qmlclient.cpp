#include "qmlclient.h"


QmlClient::QmlClient(QObject *parent)
    :QObject(parent)
    , _client(new QMQTT::Client())
{
    _client->setParent(parent);
    _client->setAutoReconnect(true);
//    connect(_client, SIGNAL(connected()), this, SLOT(connected()));
    connect(_client, SIGNAL(connected()), this, SLOT(setConnectedTrue()));
    connect(_client, SIGNAL(disconnected()), this, SLOT(setConnectedFalse()));

    connect(_client, SIGNAL(subscribed(QString,quint8)), this, SLOT(subscribed(QString)));

    connect(_client, SIGNAL(received(QMQTT::Message)), this, SLOT(received(QMQTT::Message)));

}

QString QmlClient::hostString() const
{
    return _client->host().toString();
}

void QmlClient::setHostString(const QString host)
{
    QHostAddress hostAdress(host);
    if (hostAdress.isNull()){
        return;
    }else{
        _client->disconnectFromHost();
        _client->setHost(hostAdress);
        _client->connectToHost();
        emit hostStringChanged();
    }
}

int QmlClient::port() const
{
    return _client->port();
}

void QmlClient::setPort(const int port)
{
    _client->setPort(port);
    emit portChanged();
}

bool QmlClient::isConnected() const
{
    return this->_connected;
}

void QmlClient::setIsConnected(const bool status)
{
    qDebug() << "Connection status change to " << status << endl;
    if (status != this->_connected) {
        this->_connected = status;
        emit isConnectedChanged();
    }
}

QString QmlClient::subscribeTopic() const
{
    return this->_currnetTopic;
}

void QmlClient::setSubscribeTopic(const QString topic)
{
    if (topic != this->_currnetTopic){
        this->_client->unsubscribe(this->_currnetTopic);
        this->_currnetTopic = topic;
        this->_client->subscribe(this->_currnetTopic);
        emit subscribeTopicChanged();
    }
}

void QmlClient::publishMsg(const quint16 id, const QString &topic, const QString &message)
{
    QMQTT::Message message_object(id, topic, message.toUtf8());
    _client->publish(message_object);
}



void QmlClient::subscribed(QString topic)
{
    qDebug() << "Subscribed to " << topic << endl;
}

void QmlClient::received(QMQTT::Message message)
{
    emit newMessage(message.topic(),QString::fromUtf8(message.payload()));
}

void QmlClient::setConnectedTrue()
{
    _client->subscribe(this->_currnetTopic);
    this->setIsConnected(true);
}

void QmlClient::setConnectedFalse()
{
    this->setIsConnected(false);
}
