#pragma once

#include <list>
#include <memory>
#include <string>
#include <functional>

#include "creature.h"
#include "unbound_command.h"
#include "bound_command.h"

class SimpleCommand : public UnboundCommand {
    public:
        SimpleCommand(std::string _name)
            : name(_name)
        { }

        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;

    protected:
        virtual std::function<void()> getExecutor() = 0;

        std::string name;
};