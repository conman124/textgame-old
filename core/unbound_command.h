#pragma once

#include <memory>
#include <list>
#include <string>

#include "creature.h"
#include "bound_command.h"

class UnboundCommand {
    public:
        virtual std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) = 0;
        virtual ~UnboundCommand() {};
};