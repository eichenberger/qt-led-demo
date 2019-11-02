#ifndef LED_H
#define LED_H

#include <QObject>
#include <QPointer>

#include "gpio.h"

class Led : public QObject
{
    Q_OBJECT
public:
    explicit Led(QObject *parent = nullptr);
    ~Led();

signals:

public slots:
    void enable();
    void disable();

private:
    QPointer<Gpio> gpio;
};

#endif // LED_H
