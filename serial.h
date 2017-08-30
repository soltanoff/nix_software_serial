#ifndef CSOFTWARESERIAL_H
#define CSOFTWARESERIAL_H

#include <iostream>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>


static const int BAUD_RATE = B9600;
static const char *SERIAL_PORTS[38] = {
        "/dev/ttyS0",   "/dev/ttyS1",   "/dev/ttyS2",   "/dev/ttyS3",   "/dev/ttyS4",   "/dev/ttyS5",
        "/dev/ttyS6",   "/dev/ttyS7",   "/dev/ttyS8",   "/dev/ttyS9",   "/dev/ttyS10",  "/dev/ttyS11",
        "/dev/ttyS12",  "/dev/ttyS13",  "/dev/ttyS14",  "/dev/ttyS15",  "/dev/ttyUSB0", "/dev/ttyUSB1",
        "/dev/ttyUSB2", "/dev/ttyUSB3", "/dev/ttyUSB4", "/dev/ttyUSB5", "/dev/ttyAMA0", "/dev/ttyAMA1",
        "/dev/ttyACM0", "/dev/ttyACM1", "/dev/rfcomm0", "/dev/rfcomm1", "/dev/ircomm0", "/dev/ircomm1",
        "/dev/cuau0",   "/dev/cuau1",   "/dev/cuau2",   "/dev/cuau3",   "/dev/cuaU0",   "/dev/cuaU1",
        "/dev/cuaU2",   "/dev/cuaU3"
};


class CSoftwareSerial {
public:
    CSoftwareSerial();

    bool openSerial(const int port);

    int pollSerial(const int port, char *buf) const;

    int sendData(const int port, const char *buf) const;

    void closeSerial(const int port);

    void reset(const int port);

    void flush(const int port);

private:
    int _error;
    // int _port[12];
    struct termios _newPortSettings;
    struct termios _oldPortSettings[22];
};

#endif /* CSOFTWARESERIAL_H */


