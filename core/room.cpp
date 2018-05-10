#include "room.h"

Room::Room(Driver& _driver)
    : driver(_driver)
    , creatures()
{

}

const std::unordered_set<std::shared_ptr<Creature>>& Room::getCreatures() {
    return this->creatures;
}

void Room::addCreature(std::shared_ptr<Creature> creature) {
    this->creatures.insert(creature);
}
void Room::removeCreature(std::shared_ptr<Creature> creature) {
    this->creatures.erase(creature);
}