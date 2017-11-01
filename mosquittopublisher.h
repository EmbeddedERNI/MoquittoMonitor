#ifndef MOSQUITTOPUBLISHER_H
#define MOSQUITTOPUBLISHER_H

#include <qmqtt.h>
#include <QTimer>
#include <QCoreApplication>
#include <QDebug>

class MosquittoPublisher : public QMQTT::Client
{
    Q_OBJECT
public:
    explicit MosquittoPublisher(const QHostAddress& host ,
                       const quint16 port ,
                       QObject* parent = NULL)
        : QMQTT::Client(host, port, parent)
        , _number(0)
    {
        connect(this, &MosquittoPublisher::connected, this, &MosquittoPublisher::onConnected);
        connect(&_timer, &QTimer::timeout, this, &MosquittoPublisher::onTimeout);
        connect(this, &MosquittoPublisher::disconnected, this, &MosquittoPublisher::onDisconnected);
        qDebug() << "Setup complete";
    }
    virtual ~MosquittoPublisher() {}

    QTimer _timer;
    quint16 _number;

public slots:
    void onConnected()
    {
        subscribe("EXAMPLE_TOPIC", 0);
        _timer.start(1000);
    }

    void onTimeout()
    {
        QMQTT::Message message(_number, "EXAMPLE_TOPIC",
                               QString("Number is %1").arg(_number).toUtf8());
        publish(message);
        qDebug() << "Number: " << _number;
        _number++;

        if(_number >= 10)
        {
            _timer.stop();
            disconnectFromHost();
        }
    }

    void onDisconnected()
    {
        qDebug() << "Disconected";
        QTimer::singleShot(0, qApp, &QCoreApplication::quit);
    }
};


#endif // MOSQUITTOPUBLISHER_H
