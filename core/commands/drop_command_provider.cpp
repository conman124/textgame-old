#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "../creature.h"
#include "../room.h"
#include "../simple_command.h"
#include "drop_command_provider.h"

namespace {
	typedef std::tuple<std::string> StringTuple;

	std::string name = "drop";

	Parameterizer<StringTuple> parameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
		// Ensure that there are more parameters
		// (CommmandWordIterator() will be equal the "end" iterator)
		if(commandParameters == CommandWordIterator()) {
			// If not return empty optional
			return OptionalParameterTuple<StringTuple>();
		}

		// For now, this assumes that items only have one word as their name
		// TODO fix that

		std::string itemName = *commandParameters;
		commandParameters++;

		// This is invalid if there's anything after the item name
		if(commandParameters != CommandWordIterator()) {
			return OptionalParameterTuple<StringTuple>();
		}

		std::cout.flush();

		if(!actor.getItemContainer().contains(itemName)) {
			return OptionalParameterTuple<StringTuple>();
		}
		std::cout.flush();

		return OptionalParameterTuple<StringTuple>(std::make_tuple(itemName));
	};
	Executor<StringTuple> executor = [](Creature& actor, StringTuple&& tuple) {
		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);
		std::cout.flush();
		
		actor.getItemContainer().moveItemsInto(std::get<0>(tuple), room->getItemContainer());
		std::cout << "You drop " << std::get<0>(tuple) << "." << std::endl;
	};

	class DropCommand : public SimpleCommand<name, StringTuple, parameterizer, executor> { };
}

void provideDropCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<DropCommand>());
}