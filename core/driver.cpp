#include <unistd.h>
#include <thread>
#include <mutex>
#include <iostream>
#include <list>
#include <memory>

#include "driver.h"
#include "bound_command.h"
#include "unbound_command.h"
#include "simple_command.h"
#include "room.h"
#include "player.h"
#include "commands/core_command_provider.h"

Driver::Driver() 
    : roomMaintainer()
    , player(std::make_shared<Player>(*this))
    , coreCommands(CoreCommandProvider().getCommands())
{
    std::shared_ptr<Room> rooms[3][3];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			rooms[i][j] = std::make_shared<Room>(*this);

			std::ostringstream ss;
			ss << "Description is " << i << "," << j;
			rooms[i][j]->setDescription(ss.str());

			if(i > 0) {
				rooms[i-1][j]->addExit("south", rooms[i][j]);
				rooms[i][j]->addExit("north", rooms[i-1][j]);

				if(j > 0) {
					rooms[i-1][j-1]->addExit("southeast", rooms[i][j]);
					rooms[i][j]->addExit("northwest", rooms[i-1][j-1]);
				}
			}

			if(j > 0) {
				rooms[i][j-1]->addExit("east", rooms[i][j]);
				rooms[i][j]->addExit("west", rooms[i][j-1]);
			}

			this->roomMaintainer.visit(rooms[i][j]);
		}
	}

    this->player->moveToRoom(rooms[1][1]);
}

void Driver::queueCommand(std::string command) {
	if(command.length() == 0) { return; }

	std::cout << "Command: " << command << std::endl;

	std::list<std::unique_ptr<BoundCommand>> boundCommands = this->attemptCommandResolution(this->player, command);
	if(boundCommands.size() != 1) {
		std::cout << "I'm not sure what you mean..." << std::endl;
	} else {
		boundCommands.front()->execute();
	}
}

std::list<std::unique_ptr<BoundCommand>> Driver::attemptCommandResolution(std::shared_ptr<Creature> actor, std::string command) {
    std::list<std::unique_ptr<BoundCommand>> boundCommands;

    for(auto& unboundCommand : this->coreCommands) {
        auto someBoundCommands = unboundCommand->resolve(actor, command);
        boundCommands.splice(boundCommands.end(), someBoundCommands, someBoundCommands.begin(), someBoundCommands.end());
    }
    return boundCommands;
}