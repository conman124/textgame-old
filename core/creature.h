#pragma once

#include <memory.h>

#include "room.h"

class Room;

class Creature : public std::enable_shared_from_this<Creature> {
    public:
        Creature();
        const std::weak_ptr<Room>& getRoom();
        void moveToRoom(std::shared_ptr<Room> room);
        void moveToRoom(std::weak_ptr<Room> room);
    protected:
        std::weak_ptr<Room> room;
};