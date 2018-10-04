#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "../creature.h"
#include "../room.h"
#include "../simple_command.h"
#include "inventory_command_provider.h"

namespace {
	typedef std::tuple<> EmptyTuple;

	std::string name = "inventory";
	std::string shortName = "i";

	Parameterizer<EmptyTuple> parameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
		(void)actor;
		
		// Ensure that there are no more parameters
		// (CommmandWordIterator() will be equal the "end" iterator)
		if(commandParameters != CommandWordIterator()) {
			return OptionalParameterTuple<EmptyTuple>();
		}

		return OptionalParameterTuple<EmptyTuple>(std::make_tuple());
	};
	Executor<EmptyTuple> executor = [](Creature& actor, EmptyTuple&& tuple) {
		(void)tuple;
		std::cout << actor.getItemContainer().describe() << std::endl;
	};

	class InventoryCommand : public SimpleCommand<name, EmptyTuple, parameterizer, executor> { };
	class ShortInventoryCommand : public SimpleCommand<shortName, EmptyTuple, parameterizer, executor> { };
}

void provideInventoryCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<InventoryCommand>());
	commandList.push_back(std::make_unique<ShortInventoryCommand>());
}
