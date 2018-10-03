#include <memory>

#include "../unbound_command.h"

#include "core_command_provider.h"
#include "backflip_command_provider.h"
#include "go_command_provider.h"

std::list<std::unique_ptr<UnboundCommand>> CoreCommandProvider::getCommands() {
    std::list<std::unique_ptr<UnboundCommand>> ret;

	provideBackflipCommands(ret);
	provideGoCommands(ret);

    return ret;
}