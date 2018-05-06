#include <unistd.h>
#include <iostream>

#include "driver.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Driver driver;

    while(std::cin) {
        std::string command;
        std::getline(std::cin, command);

        driver.queueCommand(command);
    }

    return 0;
}