#pragma once

#include <list>
#include <memory>

#include "../unbound_command.h"

void provideTakeCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);