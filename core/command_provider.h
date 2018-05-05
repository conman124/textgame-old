#pragma once

#include <list>
#include <memory>

#include "unbound_command.h"

class ICommandProvider {
    public:
        virtual std::list<std::unique_ptr<UnboundCommand>> getCommands() = 0;
        virtual ~ICommandProvider() {}
};