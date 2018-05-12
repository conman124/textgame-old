#include "room.h"

#include <iostream>

template <class T>
bool operator==(const std::weak_ptr<T> weak, std::nullptr_t);

template <class T>
bool operator==(const std::weak_ptr<T> weak, std::nullptr_t) {
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

Room::Room(Driver& _driver)
    : driver(_driver)
    , creatures()
    , exits()
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

void Room::addExit(std::string name, std::shared_ptr<Room> room) {
    this->exits[name] = std::weak_ptr<Room>(room);
}

std::shared_ptr<Room> Room::getExit(std::string name) {
    return (this->exits[name] == nullptr) ? nullptr : this->exits[name].lock();
}