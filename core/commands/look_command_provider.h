#pragma once

#include <list>
#include <memory>

#include "../creature.h"

void provideLookCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);
std::unique_ptr<BoundCommand> constructRoomLookCommand(std::shared_ptr<Creature> actor);