#pragma once

#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <iterator>
#include <functional>
#include <tuple>
#include <optional>

#include "creature.h"
#include "unbound_command.h"
#include "bound_command.h"


template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<std::optional<ParameterTuple>(std::istream_iterator<std::string>)>& Parameterizer,
    const std::function<void(Creature&, ParameterTuple&&)>& Executor
>
class SimpleCommand: public UnboundCommand {
    public:
        virtual ~SimpleCommand() { }
        std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command) override final;
    private:
        static bool doesCommandMatchName(std::istream_iterator<std::string>& command);
};

template <typename ParameterTuple>
class SimpleBoundCommand : public BoundCommand {
    public:
        SimpleBoundCommand(std::shared_ptr<Creature> _actor, std::function<void(Creature&, ParameterTuple&&)> _executor, ParameterTuple&& _tuple)
            : BoundCommand(_actor)
            , executor(_executor)
            , tuple(std::move(_tuple))
        { }

        void execute() override {
            this->executor(*this->actor, std::move(this->tuple));
        }

    private:
        std::function<void(Creature&, ParameterTuple&&)> executor;
        ParameterTuple tuple;
};

template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<std::optional<ParameterTuple>(std::istream_iterator<std::string>)>& Parameterizer,
    const std::function<void(Creature&, ParameterTuple&&)>& Executor
>
std::list<std::unique_ptr<BoundCommand>> SimpleCommand<Name, ParameterTuple, Parameterizer, Executor>::resolve(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;
    std::istringstream commandWordStream(command);
    std::istream_iterator<std::string> commandwords(commandWordStream);

    if(this->doesCommandMatchName(commandwords)) {
        std::optional<ParameterTuple>&& parameterization = std::move(Parameterizer(commandwords));
        if(parameterization) {
            boundCommands.push_back(std::move(std::make_unique<SimpleBoundCommand<ParameterTuple>>(actor, Executor, std::move(*parameterization))));
        }
    }

    return boundCommands;
}

template <
    const std::string& Name,
    typename ParameterTuple,
    const std::function<std::optional<ParameterTuple>(std::istream_iterator<std::string>)>& Parameterizer,
    const std::function<void(Creature&, ParameterTuple&&)>& Executor
>
bool SimpleCommand<Name, ParameterTuple, Parameterizer, Executor>::doesCommandMatchName(std::istream_iterator<std::string>& commandwords) {
    std::istringstream nameWordStream(Name);
    std::istream_iterator<std::string> namewords(nameWordStream);

    std::istream_iterator<std::string> end;

    while(namewords != end) {
        if(commandwords == end || *namewords != *commandwords) {
            return false;
        }
        namewords++;
        commandwords++;
    }
    return true;
}

template <typename ParameterTuple>
using Parameterizer = std::function<std::optional<ParameterTuple>(std::istream_iterator<std::string>)>;

template <typename ParameterTuple>
using OptionalParameterTuple = std::optional<ParameterTuple>;

typedef std::istream_iterator<std::string> CommandWordIterator;

template <typename ParameterTuple>
using Executor = std::function<void(Creature&, ParameterTuple&&)>;