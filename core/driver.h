#pragma once

#define HEARTBEAT_US 1000000

#include <thread>
#include <mutex>
#include <queue>
#include <string>

#include "player.h"

class Driver {
    public:
        Driver()
            : running(true)
            , player()
            , commandsMutex()
            , commands()
            , heartbeatThread(beginHeartbeat())
        { }

        ~Driver();

        void queueCommand(std::string command);
    private:
        bool running;

        Player player;

        std::mutex commandsMutex;
        std::queue<std::string> commands;

        std::thread beginHeartbeat();
        std::thread heartbeatThread;
        void heartbeat();
};