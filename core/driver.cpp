#include <unistd.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <list>
#include <memory>

#include "driver.h"
#include "unbound_command.h"

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
    std::list<std::unique_ptr<UnboundCommand>> unboundCommands;

    while(this->commands.size() > 0) {
        auto command = this->commands.front();
        this->commands.pop();
        if(command.length() == 0) { continue; }

        std::cout << "Command: " << command << std::endl;

        std::list<std::unique_ptr<BoundCommand>> boundCommands;
        for(auto& unboundCommand : unboundCommands) {
            auto someBoundCommands = unboundCommand->resolve(nullptr, "");
            boundCommands.splice(boundCommands.end(), someBoundCommands, someBoundCommands.begin(), someBoundCommands.end());
        }
        if(boundCommands.size() != 1) {
            std::cout << "I'm not sure what you mean..." << std::endl;
        } else {
            boundCommands.front()->execute();
        }
    }
}