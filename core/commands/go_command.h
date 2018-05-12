#include <string>
#include <tuple>
#include <cassert>
#include <memory>
#include <iostream>

#include "../simple_command.h"
#include "../creature.h"
#include "../room.h"

std::string goCommandName = "go";
typedef std::tuple<std::shared_ptr<Room>> RoomDirectionTuple;
Parameterizer<RoomDirectionTuple> goParameterizer = [](Creature& actor, CommandWordIterator commandWords) {
    auto roomWeak = actor.getRoom();
    std::shared_ptr<Room> room;
    assert((room = roomWeak.lock()) != nullptr);

    if(commandWords == CommandWordIterator()) {
        return OptionalParameterTuple<RoomDirectionTuple>();
    }
    std::ostringstream out;
    out << *commandWords;
    commandWords++;
    std::istream_iterator<std::string> end;
    while(commandWords != end) {
        out << " " << *commandWords;
        commandWords++;
    }

    auto toRoom = room->getExit(out.str());
    if(toRoom == nullptr) {
        return OptionalParameterTuple<RoomDirectionTuple>();
    }

    return OptionalParameterTuple<RoomDirectionTuple>(std::make_tuple(toRoom));
};
Executor<RoomDirectionTuple> goExecutor = [](Creature& actor, RoomDirectionTuple newRoom) {
    actor.moveToRoom(std::get<0>(newRoom));
};

class GoCommand : public SimpleCommand<goCommandName,RoomDirectionTuple,goParameterizer,goExecutor> {};