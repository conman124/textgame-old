#include <unistd.h>
#include <thread>
#include <mutex>
#include <iostream>

#include "driver.h"

Driver::~Driver() {
    this->running = false;
    this->heartbeatThread.join();
}

std::thread Driver::beginHeartbeat() {
    return std::thread([this]() {
        while(this->running) {
            usleep(HEARTBEAT_US);

            this->heartbeat();
        }
    });
}

void Driver::queueCommand(std::string command) {
    std::lock_guard<std::mutex> lock(this->commandsMutex);
    this->commands.push(command);
}

void Driver::heartbeat() {
    std::lock_guard<std::mutex> lock(this->commandsMutex);
    while(this->commands.size() > 0) {
        auto command = this->commands.front();
        this->commands.pop();

        std::cout << "Command: " << command << std::endl;
    }
}