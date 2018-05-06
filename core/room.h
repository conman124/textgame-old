#pragma once

#include <unordered_set>
#include <memory>

#include "creature.h"

class Creature;

class Room {
    public:
        Room();
        const std::unordered_set<std::shared_ptr<Creature>>& getCreatures();
        void addCreature(std::shared_ptr<Creature> creature);
        void removeCreature(std::shared_ptr<Creature> creature);
    private:
        std::unordered_set<std::shared_ptr<Creature>> creatures;
};