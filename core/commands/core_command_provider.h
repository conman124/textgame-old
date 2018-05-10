#include <list>
#include <memory>

#include "../command_provider.h"

class UnboundCommand;

class CoreCommandProvider : public ICommandProvider {
    public:
        std::list<std::unique_ptr<UnboundCommand>> getCommands() final override;
};