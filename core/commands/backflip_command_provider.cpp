#include <string>
#include <iostream>
#include <list>
#include <memory>

#include "../simple_command.h"
#include "backflip_command_provider.h"

namespace {
	typedef std::tuple<std::string> StringTuple;
	typedef std::tuple<> EmptyTuple;

	std::string name = "backflip";

	Parameterizer<StringTuple> adverbParameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
		(void)actor;

		// Ensure that there are more parameters
		// (CommmandWordIterator() will be equal the "end" iterator)
		if(commandParameters == CommandWordIterator()) {
			// If not return empty optional
			return OptionalParameterTuple<StringTuple>();
		}
		std::ostringstream out;
		out << *commandParameters;
		commandParameters++;
		std::istream_iterator<std::string> end;
		while(commandParameters != end) {
			out << " " << *commandParameters;
			commandParameters++;
		}
		return OptionalParameterTuple<StringTuple>(std::make_tuple(out.str()));
	};
	Executor<StringTuple> adverbExecutor = [](Creature& actor, StringTuple&& tuple) {
		(void)actor;
		std::cout << "You backflip " << std::get<0>(tuple) << "!" << std::endl;
	};


	Parameterizer<EmptyTuple> plainParameterizer = [](Creature& actor, CommandWordIterator commandParameters) -> OptionalParameterTuple<EmptyTuple> {
		(void)actor;
		// If there are more parameter, return empty optional,
		// because that is an adverb command
		if(commandParameters != CommandWordIterator()) {
			return OptionalParameterTuple<EmptyTuple>();
		}
		return OptionalParameterTuple<EmptyTuple>(std::make_tuple());
	};
	Executor<EmptyTuple> plainExecutor = [](Creature& actor, EmptyTuple&& tuple) {
		(void)tuple;
		(void)actor;
		std::cout << "You backflip!" << std::endl;
	};

	class BackflipAdverbCommand : public SimpleCommand<name, StringTuple, adverbParameterizer, adverbExecutor> { };
	class BackflipPlainCommand : public SimpleCommand<name, EmptyTuple, plainParameterizer, plainExecutor> { };
}

void provideBackflipCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList) {
    commandList.push_back(std::make_unique<BackflipAdverbCommand>());
    commandList.push_back(std::make_unique<BackflipPlainCommand>());
}