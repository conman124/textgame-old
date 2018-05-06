#include <iostream>

#include "simple_command.h"
#include "bound_command.h"

// TODO totally revamp this, potentially using templates for name, executor, and for getting command parameters
// TODO give executor access to actor somehow
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

std::list<std::unique_ptr<BoundCommand>> SimpleCommand::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    // TODO rework the check to determine if this is the right command.
    if(command.compare(0, this->name.length(), this->name) == 0) {
        boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand>(actor, this->getExecutor())));
    }
    return boundCommands;
}