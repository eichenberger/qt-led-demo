#include <QDirIterator>
#include <QDebug>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <linux/gpio.h>

#include "gpio.h"

Gpio::Gpio(QString name, QObject *parent) : QObject(parent), gpio_fd(-1)
{
    int gpio = -1;
    QString gpiochip;

    QString devdir = "/dev/";
    QDir dev(devdir);
    dev.setFilter(QDir::Files | QDir::Hidden | QDir::System);
    dev.setNameFilters(QStringList("gpiochip*"));

    QStringList fileList = dev.entryList();
    for (int i = 0; i < fileList.count() && gpio == -1; i++) {
        QString fileName = devdir + fileList[i];
        QFile f(fileName);
        f.open(QIODevice::ReadWrite);

        qDebug() << f.fileName();

        struct gpiochip_info cinfo;
        int ret = ioctl(f.handle(), GPIO_GET_CHIPINFO_IOCTL, &cinfo);
        if (ret == -1) {
            qDebug() << "Failed to issue CHIPINFO IOCTL";
            return;
        }

        /* Loop over the lines and print info */
        for (uint32_t i = 0; i < cinfo.lines; i++) {
            struct gpioline_info linfo;

            memset(&linfo, 0, sizeof(linfo));
            linfo.line_offset = i;

            ret = ioctl(f.handle(), GPIO_GET_LINEINFO_IOCTL, &linfo);
            if (ret == -1) {
                qDebug() << "Failed to issue LINEINFO IOCTL for " << i;
                continue;
            }

            if (QString(linfo.name) == name) {
                qDebug() << "GPIO " << name << " found";
                gpiochip = f.fileName();
                gpio = static_cast<int>(i);
                break;
            }
        }
    }
    if (gpio == -1) {
        qDebug() << "No gpio found";
        return;
    }
    QFile f(gpiochip);
    f.open(QIODevice::ReadWrite);
    struct gpiohandle_request req;
    req.lineoffsets[0] = static_cast<uint32_t>(gpio);
    req.lines = 1;
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    strcpy(req.consumer_label, "qtgpio");
    int ret = ioctl(f.handle(), GPIO_GET_LINEHANDLE_IOCTL, &req);
    if (ret == -1) {
        qDebug() << "Could not set gpio" << gpio << " as output";
        return;
    }
    gpio_fd = req.fd;
}

Gpio::~Gpio()
{
    close(gpio_fd);
}

void Gpio::enable()
{
    setGpio(1);
}

void Gpio::disable()
{
    setGpio(0);
}

void Gpio::setGpio(uint8_t value)
{
    struct gpiohandle_data data;
    data.values[0] = value;
    int ret = ioctl(gpio_fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    if (ret == -1) {
        qDebug() << "Could not set gpio value " << value;
    }
}
