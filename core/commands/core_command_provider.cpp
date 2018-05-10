#include <memory>

#include "core_command_provider.h"
#include "backflip_command.h"

std::list<std::unique_ptr<UnboundCommand>> CoreCommandProvider::getCommands() {
    std::list<std::unique_ptr<UnboundCommand>> ret;

    ret.push_back(std::make_unique<BackflipAdverbCommand>());
    ret.push_back(std::make_unique<BackflipPlainCommand>());

    return ret;
}