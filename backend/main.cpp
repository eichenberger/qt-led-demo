#include <QCoreApplication>

#include <QtWebSockets/QWebSocketServer>

#include "led.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Backend backend;
    return app.exec();

}
