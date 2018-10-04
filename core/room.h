#pragma once

#include <unordered_set>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "driver.h"
#include "item_container.h"
#include "traits/describable.h"

class Creature;
class Driver;
class Room;

class Room : public Describable {
    public:
        Room(Driver& driver);
        const std::unordered_set<std::shared_ptr<Creature>>& getCreatures();
        void addCreature(std::shared_ptr<Creature> creature);
        void removeCreature(std::shared_ptr<Creature> creature);

        void addExit(std::string name, std::shared_ptr<Room> room);
        std::shared_ptr<Room> getExit(std::string name);
		std::string dealiasName(std::string name);

		std::string describe();
		void setDescription(std::string _description);
		ItemContainer& getItemContainer();
    protected:
        std::unordered_set<std::shared_ptr<Creature>> creatures;
		std::string description;
        Driver& driver;
        std::unordered_map<std::string, std::weak_ptr<Room>> exits;
		ItemContainer itemContainer;
};