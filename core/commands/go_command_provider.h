#pragma once

#include <list>
#include <memory>

void provideGoCommands(std::list<std::unique_ptr<UnboundCommand>> &commandList);