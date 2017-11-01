#ifndef QMLCLIENT_H
#define QMLCLIENT_H

#include <QObject>
#include "qmqtt.h"


class QmlClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString hostip READ hostString WRITE setHostString NOTIFY hostStringChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(QString subscribeTopic READ subscribeTopic WRITE setSubscribeTopic NOTIFY subscribeTopicChanged)
 public:
    explicit QmlClient(QObject *parent = nullptr);

    QString hostString() const;
    void setHostString(const QString host);

    int port() const;
    void setPort(const int port);

    bool isConnected() const;
    void setIsConnected(const bool status);

    QString subscribeTopic() const;
    void setSubscribeTopic(const QString topic);


signals:
    void hostStringChanged();
    void portChanged();
    void isConnectedChanged();
    void subscribeTopicChanged();

    void newMessage(QString topic, QString message);

public slots:
    void publishMsg(const quint16 id, const QString &topic, const QString &message);
//    void connected();
    void subscribed(QString topic);
    void received(QMQTT::Message message);
private slots:
    void setConnectedTrue();
    void setConnectedFalse();

private:
    QMQTT::Client *_client;
    bool _connected;

    QString _currnetTopic = "/#";
};

#endif // QMLCLIENT_H
