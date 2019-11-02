#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>

#include "led.h"

class Backend : public QObject
{
    Q_OBJECT
public:
    explicit Backend(QObject *parent = nullptr);

signals:

public slots:
    void onNewConnection();

private:
    QWebSocketServer server;
};

class BackendConnection : public QObject
{
    Q_OBJECT
public:
    BackendConnection(QWebSocket *socket);

public slots:
    void onDisconnect();
    void onMessageReceived(const QString &message);

private:
    QWebSocket *socket;

};

#endif // BACKEND_H
