#include <QDebug>
#include <QString>

#include "led.h"

Led::Led(QObject *parent) : QObject(parent)
{
    gpio = new Gpio(QString("led"));
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
