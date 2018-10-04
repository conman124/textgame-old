#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "../creature.h"
#include "../room.h"
#include "../simple_command.h"
#include "take_command_provider.h"

namespace {
	typedef std::tuple<std::string> StringTuple;

	std::string name = "take";

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

		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);

		if(!room->getItemContainer().contains(itemName)) {
			return OptionalParameterTuple<StringTuple>();
		}

		return OptionalParameterTuple<StringTuple>(std::make_tuple(itemName));
	};
	Executor<StringTuple> executor = [](Creature& actor, StringTuple&& tuple) {
		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);
		
		room->getItemContainer().moveItemsInto(std::get<0>(tuple), actor.getItemContainer());
		std::cout << "You pick up " << std::get<0>(tuple) << "." << std::endl;
	};

	class TakeCommand : public SimpleCommand<name, StringTuple, parameterizer, executor> { };
}

void provideTakeCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<TakeCommand>());
}