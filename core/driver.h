#pragma once

#define HEARTBEAT_US 1000000

#include <memory>
#include <thread>
#include <mutex>
#include <queue>
#include <string>

class Player;

class Driver {
    public:
        Driver();
        ~Driver();

        void queueCommand(std::string command);
    private:
        bool running;

        std::shared_ptr<Player> player;

        std::mutex commandsMutex;
        std::queue<std::string> commands;

        std::thread beginHeartbeat();
        std::thread heartbeatThread;
        void heartbeat();
};