#pragma once

#include <memory>

#include "item_container.h"

class Driver;
class Room;

class Creature : public std::enable_shared_from_this<Creature> {
    public:
        Creature(Driver& driver);
        std::weak_ptr<Room> getRoom();
        void moveToRoom(std::shared_ptr<Room> room);
        void moveToRoom(std::weak_ptr<Room> room);
		ItemContainer& getItemContainer();
    protected:
        Driver& driver;
		ItemContainer itemContainer;
        std::weak_ptr<Room> room;
};