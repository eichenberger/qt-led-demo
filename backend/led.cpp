#include <QDebug>
#include <QString>

#include "led.h"

Led::Led(QObject *parent) : QObject(parent)
{
    gpio = new Gpio(QString("led"));
}

Led::~Led()
{
    delete gpio;
}

void Led::enable()
{
    qDebug() << "Enable LED";
    gpio->enable();
}

void Led::disable()
{
    qDebug() << "Disable LED";
    gpio->disable();
}
