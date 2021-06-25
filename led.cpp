#include <QDebug>
#include <QString>

#include "led.h"

Led::Led(QObject *parent) : QObject(parent)
{
    gpio = new Gpio(QString("MXM3_188"));
    Gpio red_led(QString("MXM3_178"));
    red_led.disable();
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
