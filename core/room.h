#pragma once

#include <unordered_set>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "driver.h"

class Creature;
class Driver;
class Room;

class Room {
    public:
        Room(Driver& driver);
        const std::unordered_set<std::shared_ptr<Creature>>& getCreatures();
        void addCreature(std::shared_ptr<Creature> creature);
        void removeCreature(std::shared_ptr<Creature> creature);

        void addExit(std::string name, std::shared_ptr<Room> room);
        std::shared_ptr<Room> getExit(std::string name);
    protected:
        Driver& driver;
        std::unordered_set<std::shared_ptr<Creature>> creatures;

        std::unordered_map<std::string, std::weak_ptr<Room>> exits;
};