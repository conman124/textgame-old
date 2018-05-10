#include <unistd.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <list>
#include <memory>

#include "driver.h"
#include "bound_command.h"
#include "unbound_command.h"
#include "simple_command.h"
#include "room.h"
#include "player.h"
#include "commands/core_command_provider.h"

Driver::Driver() 
    : roomMaintainer()
    , running(true)
    , player(std::make_shared<Player>(*this))
    , coreCommands(CoreCommandProvider().getCommands())
    , commandsMutex()
    , commands()
    , heartbeatThread(beginHeartbeat())
{
    std::shared_ptr<Room> room = std::make_shared<Room>(*this);
    this->roomMaintainer.visit(room);
    this->player->moveToRoom(room);
}

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

std::list<std::unique_ptr<BoundCommand>> Driver::attemptCommandResolution(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;

    for(auto& unboundCommand : this->coreCommands) {
        auto someBoundCommands = unboundCommand->resolve(actor, command);
        boundCommands.splice(boundCommands.end(), someBoundCommands, someBoundCommands.begin(), someBoundCommands.end());
    }
    return boundCommands;
}

void Driver::heartbeat() {
    std::lock_guard<std::mutex> lock(this->commandsMutex);

    while(this->commands.size() > 0) {
        auto command = this->commands.front();
        this->commands.pop();
        if(command.length() == 0) { continue; }

        std::cout << "Command: " << command << std::endl;

        std::list<std::unique_ptr<BoundCommand>> boundCommands = this->attemptCommandResolution(this->player, command);
        if(boundCommands.size() != 1) {
            std::cout << "I'm not sure what you mean..." << std::endl;
        } else {
            boundCommands.front()->execute();
        }
    }
}