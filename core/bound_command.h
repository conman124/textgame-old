#pragma once

#include <memory>

#include "creature.h"

class Creature;

class BoundCommand {
    public:
        BoundCommand(std::shared_ptr<Creature> _actor) : actor(_actor) { }
        virtual void execute() = 0;
        virtual ~BoundCommand() {};

    protected:
        std::shared_ptr<Creature> actor;
};