#include <cassert>
#include <string>
#include <iostream>
#include <list>
#include <memory>

#include "../creature.h"
#include "../simple_command.h"
#include "../room.h"
#include "look_command_provider.h"


namespace {
	typedef std::tuple<> EmptyTuple;

	std::string name = "look";
	std::string shortName = "l";

	Parameterizer<EmptyTuple> parameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
		(void)actor;

		// Ensure that there are no more parameters
		// (CommmandWordIterator() will equal the "end" iterator)
		if(commandParameters != CommandWordIterator()) {
			// If there are more return empty optional
			return OptionalParameterTuple<EmptyTuple>();
		}
		return OptionalParameterTuple<EmptyTuple>(std::make_tuple());
	};
	Executor<EmptyTuple> executor = [](Creature& actor, EmptyTuple&& tuple) {
		(void)tuple;
		
		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);

		std::cout << room->getDescription() << std::endl;
	};

	class LookCommand : public SimpleCommand<name, EmptyTuple, parameterizer, executor> { };
	class ShortLookCommand : public SimpleCommand<shortName, EmptyTuple, parameterizer, executor> { };
}

void provideLookCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<LookCommand>());
	commandList.push_back(std::make_unique<ShortLookCommand>());
}