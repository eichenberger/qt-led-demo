#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "led.h"

int main(int argc, char *argv[])
{
    qmlRegisterType<Led>("led", 1, 0, "Led");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
