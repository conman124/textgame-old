#include <memory>
#include <cassert>
#include <iostream>

#include "creature.h"
#include "room.h"

Creature::Creature(Driver& _driver)
    : driver(_driver)
    , room()
{

}

std::weak_ptr<Room> Creature::getRoom() {
    return this->room;
}

void Creature::moveToRoom(std::weak_ptr<Room> _room) {
    this->moveToRoom(_room.lock());
}

void Creature::moveToRoom(std::shared_ptr<Room> _room) {
    assert(_room != nullptr);
    
    if(auto oldRoom = this->room.lock()) {
        oldRoom->removeCreature(this->shared_from_this());
    }
    _room->addCreature(this->shared_from_this());
    this->room = std::weak_ptr<Room>(_room);
}