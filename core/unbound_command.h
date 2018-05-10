#pragma once

#include <memory>
#include <list>
#include <string>

class Creature;
class BoundCommand;

class UnboundCommand {
    public:
        virtual std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) = 0;
        virtual ~UnboundCommand() {};
};