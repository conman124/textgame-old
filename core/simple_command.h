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
    const std::string& name,
    typename parameterTuple,
    const std::function<void(parameterTuple&)>& executor,
    const std::function<parameterTuple()>& parameterizer
>
class SimpleCommand: public UnboundCommand {
    public:
        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;
};

template <typename parameterTuple>
class SimpleBoundCommand : public BoundCommand {
    public:
        SimpleBoundCommand(std::shared_ptr<Creature> _actor, std::function<void(parameterTuple&)> _executor, parameterTuple _tuple)
            : BoundCommand(_actor)
            , executor(_executor)
            , tuple(_tuple)
        { }

        void execute() override {
            this->executor(this->tuple);
        }

    private:
        std::function<void(parameterTuple&)> executor;
        parameterTuple tuple;
};

template <
    const std::string& name,
    typename parameterTuple,
    const std::function<void(parameterTuple&)>& executor,
    const std::function<parameterTuple()>& parameterizer
>
std::list<std::unique_ptr<BoundCommand>> SimpleCommand<name, parameterTuple, executor, parameterizer>::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    // TODO rework the check to determine if this is the right command.
    if(command.compare(0, name.length(), name) == 0) {
        boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand<parameterTuple>>(actor, executor, parameterizer())));
    }
    return boundCommands;
}