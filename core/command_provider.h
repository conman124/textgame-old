#pragma once

#include <list>
#include <memory>

class UnboundCommand;

class ICommandProvider {
    public:
        virtual std::list<std::unique_ptr<UnboundCommand>> getCommands() = 0;
        virtual ~ICommandProvider() {}
};