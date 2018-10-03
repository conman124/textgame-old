#pragma once

#include <list>
#include <memory>

#include "../creature.h"
#include "../unbound_command.h"

namespace {
	class DirectionCommand : public UnboundCommand {
		public:
			std::list<std::unique_ptr<BoundCommand>> resolve(std::shared_ptr<Creature> actor, std::string command);
	};
}

void provideGoCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);