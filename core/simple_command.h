#pragma once

#include <list>
#include <memory>
#include <string>
#include <functional>

#include "creature.h"
#include "unbound_command.h"
#include "bound_command.h"


// TODO command parameters: maybe a method that returns a tuple of parameters that the executor will receive
// TODO give executor access to actor somehow
template <const std::string& name, const std::function<void()>& executor>
class SimpleCommand: public UnboundCommand {
    public:
        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;
};

class SimpleBoundCommand : public BoundCommand {
    public:
        SimpleBoundCommand(std::shared_ptr<Creature> _actor, std::function<void()> _executor)
            : BoundCommand(_actor)
            , executor(_executor)
        { }

        void execute() override {
            this->executor();
        }

    private:
        std::function<void()> executor;
};

template <const std::string& name, const std::function<void()>& executor>
std::list<std::unique_ptr<BoundCommand>> SimpleCommand<name, executor>::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    // TODO rework the check to determine if this is the right command.
    if(command.compare(0, name.length(), name) == 0) {
        boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand>(actor, executor)));
    }
    return boundCommands;
}