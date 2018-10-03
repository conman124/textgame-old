#pragma once

#define HEARTBEAT_US 1000000

#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <list>

#include "room_maintainer.h"
#include "unbound_command.h"

class Creature;
class Player;
class BoundCommand;

class Driver {
    public:
        Driver();
        ~Driver() {};

        void queueCommand(std::string command);
    private:
        RoomMaintainer roomMaintainer;

        std::shared_ptr<Player> player;

        std::list<std::unique_ptr<UnboundCommand>> coreCommands;

        std::list<std::unique_ptr<BoundCommand>> attemptCommandResolution(std::shared_ptr<Creature> actor, std::string command);
};