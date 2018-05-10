#pragma once

#define HEARTBEAT_US 1000000

#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <string>
#include <list>

#include "room_maintainer.h"

class Creature;
class Player;
class UnboundCommand;
class BoundCommand;

class Driver {
    public:
        Driver();
        ~Driver();

        void queueCommand(std::string command);
    private:
        RoomMaintainer roomMaintainer;

        bool running;

        std::shared_ptr<Player> player;

        std::list<std::unique_ptr<UnboundCommand>> coreCommands;

        std::mutex commandsMutex;
        std::queue<std::string> commands;

        std::list<std::unique_ptr<BoundCommand>> attemptCommandResolution(std::shared_ptr<Creature> actor, std::string command);

        std::thread beginHeartbeat();
        std::thread heartbeatThread;
        void heartbeat();
};