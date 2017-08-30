#include "serial.h"

int _port[12];

CSoftwareSerial::CSoftwareSerial() {
}

bool CSoftwareSerial::openSerial(const int port) {
    if ((port > 38) || (port < 0)) {
        std::cout << "illegal comport number\n";
        return false;
    }

    _port[port] = open(SERIAL_PORTS[port], O_RDWR | O_NOCTTY | O_NDELAY);
    if (_port[port] == -1) {
        std::cerr << "unable to open comport ";
        return false;
    }

    _error = tcgetattr(_port[port], _oldPortSettings + port);
    if (_error == -1) {
        closeSerial(_port[port]);
        std::cerr << "unable to read portsettings ";
        return false;
    }

    memset(&_newPortSettings, 0, sizeof(_newPortSettings));

    _newPortSettings.c_cflag = BAUD_RATE | CS8 | CLOCAL | CREAD;
    _newPortSettings.c_iflag = IGNPAR;
    _newPortSettings.c_oflag = 0;
    _newPortSettings.c_lflag = 0;
    _newPortSettings.c_cc[VMIN] = 0;
    _newPortSettings.c_cc[VTIME] = 0;
    _error = tcsetattr(_port[port], TCSANOW, &_newPortSettings);
    if (_error == -1) {
        closeSerial(_port[port]);
        std::cerr << "unable to adjust portsettings ";
        return false;
    }

    return true;
}

int CSoftwareSerial::pollSerial(const int port, char *buf) const {
    return (int)read(_port[port], buf, strlen(buf));
}

int CSoftwareSerial::sendData(const int port, const char *buf) const {
    return (int)write(_port[port], buf, strlen(buf));
}

void CSoftwareSerial::closeSerial(const int port) {
    close(_port[port]);
    tcsetattr(_port[port], TCSANOW, _oldPortSettings + port);
}

void CSoftwareSerial::reset(const int port) {
    // openSerial(port);
    int mcr = !TIOCM_DTR;
    ioctl(_port[port], TIOCMSET, &mcr);
    // closeSerial(port);
}

void CSoftwareSerial::flush(const int port) {
    int n = 1;
    char buf[255];
    while (n > 0)
        n = pollSerial(port, buf);
}