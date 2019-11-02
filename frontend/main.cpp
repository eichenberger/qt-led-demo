#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QtWebSockets/QWebSocketServer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *object = engine.rootObjects().first();

    QString hostname = "localhost";
    if (qEnvironmentVariableIsSet("HOSTNAME")) {
        hostname = qEnvironmentVariable("HOSTNAME");
    }

    int port = 8081;
    if (qEnvironmentVariableIsSet("PORT")) {
        port = qEnvironmentVariable("PORT").toInt();
    }
    object->setProperty("hostname", hostname);
    object->setProperty("port", port);

    return app.exec();
}
