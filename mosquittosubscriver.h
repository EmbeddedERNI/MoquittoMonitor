#ifndef MOSQUITTOSUBSCRIVER_H
#define MOSQUITTOSUBSCRIVER_H

#include <qmqtt.h>
#include <QTimer>
#include <QDebug>

class Subscriber : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit Subscriber(const QHostAddress& host ,
                        const quint16 port ,
                        QObject* parent = NULL)
        : QMQTT::Client(host, port, parent)
        , _qout(stdout)
    {
        connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
        connect(this, SIGNAL(subscribed(QString,quint8)), this, SLOT(onSubscribed(QString)));
        connect(this, SIGNAL(received(QMQTT::Message)), this, SLOT(onReceived(QMQTT::Message)));
        this->setAutoReconnect(true);
        this->connectToHost();

    }



    QTextStream _qout;

public slots:
    void onConnected()
    {
        qDebug() << "connected" << endl;
        subscribe("/#", 0);
    }

    void onSubscribed(const QString& topic)
    {
        qDebug()  << "subscribed " << topic << endl;
    }

    void onReceived(const QMQTT::Message& message)
    {
        qDebug()  << "publish received: " << QString::fromUtf8(message.payload())
                  << " from: " << message.topic() << endl;
    }
};

#endif // MOSQUITTOSUBSCRIVER_H
