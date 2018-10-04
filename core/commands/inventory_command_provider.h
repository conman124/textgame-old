#pragma once

#include <list>
#include <memory>

#include "../unbound_command.h"

void provideInventoryCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);