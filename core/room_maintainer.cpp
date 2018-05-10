#include <memory>
#include <iostream>

#include "room_maintainer.h"

RoomMaintainer::RoomMaintainer()
    : rooms()
{

}

void RoomMaintainer::visit(std::shared_ptr<Room> room) {
    this->rooms.insert(room);
}

void RoomMaintainer::cleanup() {
    std::cerr << "RoomMaintainer::cleanup not implemented." << std::endl;
}