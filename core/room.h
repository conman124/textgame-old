#pragma once

#include <unordered_set>
#include <memory>

class Creature;
class Driver;

class Room {
    public:
        Room(Driver& driver);
        const std::unordered_set<std::shared_ptr<Creature>>& getCreatures();
        void addCreature(std::shared_ptr<Creature> creature);
        void removeCreature(std::shared_ptr<Creature> creature);
    protected:
        Driver& driver;
        std::unordered_set<std::shared_ptr<Creature>> creatures;
};