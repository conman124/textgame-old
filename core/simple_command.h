#pragma once

#include <list>
#include <memory>
#include <string>
#include <functional>
#include <tuple>

#include "creature.h"
#include "unbound_command.h"
#include "bound_command.h"


// TODO give executor access to actor somehow
template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<void(ParameterTuple&)>& Executor,
    const std::function<ParameterTuple()>& Parameterizer
>
class SimpleCommand: public UnboundCommand {
    public:
        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;
};

template <typename ParameterTuple>
class SimpleBoundCommand : public BoundCommand {
    public:
        SimpleBoundCommand(std::shared_ptr<Creature> _actor, std::function<void(ParameterTuple&)> _executor, ParameterTuple _tuple)
            : BoundCommand(_actor)
            , executor(_executor)
            , tuple(_tuple)
        { }

        void execute() override {
            this->executor(this->tuple);
        }

    private:
        std::function<void(ParameterTuple&)> executor;
        ParameterTuple tuple;
};

template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<void(ParameterTuple&)>& Executor,
    const std::function<ParameterTuple()>& Parameterizer
>
std::list<std::unique_ptr<BoundCommand>> SimpleCommand<Name, ParameterTuple, Executor, Parameterizer>::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    // TODO rework the check to determine if this is the right command.
    if(command.compare(0, Name.length(), Name) == 0) {
        boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand<ParameterTuple>>(actor, Executor, Parameterizer())));
    }
    return boundCommands;
}