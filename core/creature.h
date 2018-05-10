#pragma once

#include <memory>

class Driver;
class Room;

class Creature : public std::enable_shared_from_this<Creature> {
    public:
        Creature(Driver& driver);
        std::weak_ptr<Room> getRoom();
        void moveToRoom(std::shared_ptr<Room> room);
        void moveToRoom(std::weak_ptr<Room> room);
    protected:
        Driver& driver;
        std::weak_ptr<Room> room;
};