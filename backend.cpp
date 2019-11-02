#include "backend.h"

#include <QtWebSockets/QWebSocket>

Backend::Backend(QObject *parent) : QObject(parent), server(QString("ledbackend"), QWebSocketServer::NonSecureMode)
{
    server.listen(QHostAddress::Any, 8081);

    server.connect(&server, &QWebSocketServer::newConnection, this, &Backend::onNewConnection);
}

void Backend::onNewConnection()
{
    qDebug() << "New connection";
    BackendConnection *connection = new BackendConnection(server.nextPendingConnection());
    (void) connection;
}


BackendConnection::BackendConnection(QWebSocket *socket) :
    socket(socket)
{
    connect(socket, &QWebSocket::textMessageReceived, this, &BackendConnection::onMessageReceived);
    connect(socket, &QWebSocket::disconnected, this, &BackendConnection::onDisconnect);
}

void BackendConnection::onDisconnect()
{
    socket->close();
    delete socket;
    delete this;
}

void BackendConnection::onMessageReceived(const QString &message)
{
    Led led;
    qDebug() << "Text message received: " << message;
    if (message == "enable")
        led.enable();
    else
        led.disable();
}
