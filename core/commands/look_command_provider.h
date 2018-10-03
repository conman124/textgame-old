#pragma once

#include <list>
#include <memory>

#include "../creature.h"

void provideLookCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);