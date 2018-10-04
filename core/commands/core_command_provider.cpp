#include <memory>

#include "../unbound_command.h"

#include "core_command_provider.h"
#include "backflip_command_provider.h"
#include "go_command_provider.h"
#include "look_command_provider.h"
#include "take_command_provider.h"
#include "drop_command_provider.h"

std::list<std::unique_ptr<UnboundCommand>> CoreCommandProvider::getCommands() {
    std::list<std::unique_ptr<UnboundCommand>> ret;

	// TODO figure out a better way to do this rather than needing to manually add all of these.
	provideBackflipCommands(ret);
	provideGoCommands(ret);
	provideLookCommands(ret);
	provideTakeCommands(ret);
	provideDropCommands(ret);

    return ret;
}