#pragma once

#include <unordered_set>
#include <memory>

class Room;

/**
 * This is not currently used for much, but eventually, it will
 * be in charge of maintaining a how recently each room was visited,
 * and freeing rooms when they haven't been visited for a while.
 * This will reduce memory usage, while still making it so that objects
 * and NPCs in a certain room will stay for a while.
 */
class RoomMaintainer {
    public:
        RoomMaintainer();
        void visit(std::shared_ptr<Room> room);
        void cleanup();
    private:
        std::unordered_set<std::shared_ptr<Room>> rooms;
};