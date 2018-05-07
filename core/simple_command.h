#pragma once

#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>
#include <tuple>

#include "creature.h"
#include "unbound_command.h"
#include "bound_command.h"


// TODO give executor access to actor somehow
template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<void(ParameterTuple&&)>& Executor,
    const std::function<ParameterTuple(std::istream_iterator<std::string>)>& Parameterizer
>
class SimpleCommand: public UnboundCommand {
    public:
        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;
    private:
        static bool doesCommandMatchName(std::istream_iterator<std::string>& command);
};

template <typename ParameterTuple>
class SimpleBoundCommand : public BoundCommand {
    public:
        SimpleBoundCommand(std::shared_ptr<Creature> _actor, std::function<void(ParameterTuple&&)> _executor, ParameterTuple&& _tuple)
            : BoundCommand(_actor)
            , executor(_executor)
            , tuple(std::move(_tuple))
        { }

        void execute() override {
            this->executor(std::move(this->tuple));
        }

    private:
        std::function<void(ParameterTuple&&)> executor;
        ParameterTuple tuple;
};

template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<void(ParameterTuple&&)>& Executor,
    const std::function<ParameterTuple(std::istream_iterator<std::string>)>& Parameterizer
>
std::list<std::unique_ptr<BoundCommand>> SimpleCommand<Name, ParameterTuple, Executor, Parameterizer>::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    std::istringstream commandWordStream(command);
    std::istream_iterator<std::string> commandwords(commandWordStream);

    if(this->doesCommandMatchName(commandwords)) {
        boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand<ParameterTuple>>(actor, Executor, std::move(Parameterizer(commandwords)))));
    }

    return boundCommands;
}

template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<void(ParameterTuple&&)>& Executor,
    const std::function<ParameterTuple(std::istream_iterator<std::string>)>& Parameterizer
>
bool SimpleCommand<Name, ParameterTuple, Executor, Parameterizer>::doesCommandMatchName(std::istream_iterator<std::string>& commandwords) {
    std::istringstream nameWordStream(Name);
    std::istream_iterator<std::string> namewords(nameWordStream);

    std::istream_iterator<std::string> end;

    while(namewords != end) {
        if(commandwords == end || *namewords != *commandwords) {
            return false;
        }
        namewords++;
        commandwords++;
    }
    return true;
}