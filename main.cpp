#include "serial.h"


void sendData(const CSoftwareSerial& port) {
    const char *str[2] = {
            "Test, test, test",
            "This is serial"
    };

    for (int i = 0; i < 3; i++) {
        port.sendData(1, str[i]);
        std::cout << "sent: `%s`\n" << str[i];
        usleep(1000000);
    }
}


void receiveData(const CSoftwareSerial& port) {
    char buf[512];

    for (int i = 0; i < 3; i++) {
        port.pollSerial(1, buf);
        std::cout << "recv: `%s`\n" << buf;
        usleep(1000000);
    }
}


int main(int argc, char* argv[]) {
    argc = 3;

    if (argc < 3)
        std::cerr << "Not enough arguments\n";
    else {
        CSoftwareSerial port;
        if (!(port.openSerial(1))) {
            std::cerr << "Can not open comport\n";
            return -1;
        }

        if (strcmp(argv[1], "-s") == 0)
            sendData(port);
        else if (strcmp(argv[1], "-c") == 0)
            receiveData(port);
    }
    return 0;
}
