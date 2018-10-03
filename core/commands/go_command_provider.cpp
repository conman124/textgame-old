#include <string>
#include <tuple>
#include <cassert>
#include <memory>
#include <iostream>

#include "../simple_command.h"
#include "../creature.h"
#include "../room.h"
#include "go_command_provider.h"

namespace {
	typedef std::tuple<std::shared_ptr<Room>> RoomDirectionTuple;

	std::string name = "go";

	Parameterizer<RoomDirectionTuple> parameterizer = [](Creature& actor, CommandWordIterator commandWords) {
		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);

		// Ensure that there's actually a direction given
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
		// If there's no exit in the given direction, this command
		// isn't valid
		if(toRoom == nullptr) {
			return OptionalParameterTuple<RoomDirectionTuple>();
		}

		return OptionalParameterTuple<RoomDirectionTuple>(std::make_tuple(toRoom));
	};

	Executor<RoomDirectionTuple> executor = [](Creature& actor, RoomDirectionTuple newRoom) {
		actor.moveToRoom(std::get<0>(newRoom));
	};

	class GoCommand : public SimpleCommand<name,RoomDirectionTuple,parameterizer,executor> {};
}

void provideGoCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
	commandList.push_back(std::make_unique<GoCommand>());
}