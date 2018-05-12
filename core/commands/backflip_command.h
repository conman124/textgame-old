#include <string>
#include <iostream>

#include "../simple_command.h"

std::string backflipCommandName = "backflip";
typedef std::tuple<std::string> StringTuple;
Parameterizer<StringTuple> backflipAdverbParameterizer = [](Creature& actor, CommandWordIterator commandParameters) {
    (void)actor;
    if(commandParameters == CommandWordIterator()) {
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
    return OptionalParameterTuple<StringTuple>(std::make_tuple<std::string>(out.str()));
};
Executor<StringTuple> backflipAdverbExecutor = [](Creature& actor, StringTuple&& tuple) {
    (void)actor;
    std::cout << "You backflip " << std::get<0>(tuple) << "!" << std::endl;
};


typedef std::tuple<> EmptyTuple;
Parameterizer<EmptyTuple> backflipPlainParameterizer = [](Creature& actor, CommandWordIterator commandParameters) -> OptionalParameterTuple<EmptyTuple> {
    (void)actor;
    if(commandParameters != CommandWordIterator()) {
        return OptionalParameterTuple<EmptyTuple>();
    }
    return OptionalParameterTuple<EmptyTuple>(std::make_tuple<>());
};
Executor<EmptyTuple> backflipPlainExecutor = [](Creature& actor, EmptyTuple&& tuple) {
    (void)tuple;
    (void)actor;
    std::cout << "You backflip!" << std::endl;
};

class BackflipAdverbCommand : public SimpleCommand<backflipCommandName, StringTuple, backflipAdverbParameterizer, backflipAdverbExecutor> { };
class BackflipPlainCommand : public SimpleCommand<backflipCommandName, EmptyTuple, backflipPlainParameterizer, backflipPlainExecutor> { };