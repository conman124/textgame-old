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
	typedef std::tuple<std::shared_ptr<Describable>> DescribableTuple;

	std::string name = "look";
	std::string shortName = "l";

	Parameterizer<DescribableTuple> parameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
		(void)actor;

		// Ensure that there are no more parameters
		// (CommmandWordIterator() will equal the "end" iterator)
		if(commandParameters != CommandWordIterator()) {
			// If there are more return empty optional
			return OptionalParameterTuple<DescribableTuple>();
		}

		auto roomWeak = actor.getRoom();
		std::shared_ptr<Room> room;
		assert((room = roomWeak.lock()) != nullptr);

		return OptionalParameterTuple<DescribableTuple>(std::make_tuple(room));
	};
	Executor<DescribableTuple> executor = [](Creature& actor, DescribableTuple&& tuple) {
		(void)actor;

		auto describable = std::get<0>(tuple);
		std::cout << describable->describe() << std::endl;
	};

	class LookCommand : public SimpleCommand<name, DescribableTuple, parameterizer, executor> { };
	class ShortLookCommand : public SimpleCommand<shortName, DescribableTuple, parameterizer, executor> { };
}

void provideLookCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<LookCommand>());
	commandList.push_back(std::make_unique<ShortLookCommand>());
}