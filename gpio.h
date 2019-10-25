#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <QString>

class Gpio : public QObject
{
    Q_OBJECT
public:
    Gpio(QString name, QObject *parent = nullptr);
    ~Gpio();

    void enable();
    void disable();

    void setGpio(uint8_t value);
private:
    int gpio_fd;
};

#endif // GPIO_H
