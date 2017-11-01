#include <QGuiApplication>
#include <QQmlApplicationEngine>




#include <QApplication>
#include <QTimer>



//const QHostAddress EXAMPLE_HOST = QHostAddress("192.168.0.164");
//const quint16 EXAMPLE_PORT = 1883;
//const QString EXAMPLE_TOPIC = "qmqtt/exampletopic";


//int main(int argc, char** argv)
//{
//    QCoreApplication app(argc, argv);
////    Subscriber subscriber;
////    subscriber.connectToHost();
//    qDebug() << "Starting";
//    MosquittoPublisher publisher(EXAMPLE_HOST, EXAMPLE_PORT);
//    publisher.connectToHost();
//    return app.exec();
//}

#include "qmlclient.h"
//#include "mosquittosubscriver.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterType<QmlClient>("QMQTT",1,0,"MQTTClient");

    qDebug() <<"Starting";
//    Subscriber subs(QHostAddress("192.168.0.164"),1883,nullptr);
    app.setOrganizationName("ERNI");
    app.setOrganizationDomain("erni.com");
    app.setApplicationName("mosquitto monitor");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
