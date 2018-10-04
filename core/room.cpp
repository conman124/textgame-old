#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#include "room.h"
#include "item_container.h"

Room::Room(Driver& _driver)
    : creatures()
	, description("")
	, driver(_driver)
    , exits()
	, itemContainer(std::make_unique<RoomItemContainerFormatter>())
{

}

const std::unordered_set<std::shared_ptr<Creature>>& Room::getCreatures() {
    return this->creatures;
}

void Room::addCreature(std::shared_ptr<Creature> creature) {
    this->creatures.insert(creature);
}
void Room::removeCreature(std::shared_ptr<Creature> creature) {
    this->creatures.erase(creature);
}

void Room::addExit(std::string name, std::shared_ptr<Room> room) {
    this->exits[name] = std::weak_ptr<Room>(room);
}

std::shared_ptr<Room> Room::getExit(std::string name) {
	name = this->dealiasName(name);
	if(this->exits.find(name) == this->exits.end()) {
		return nullptr;
	}
    return this->exits[name].lock();
}

std::string Room::dealiasName(std::string name) {
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if(name == "n") {
		name = "north";
	} else if (name == "ne") {
		name = "northeast";
	} else if (name == "e") {
		name = "east";
	} else if (name == "se") {
		name = "southeast";
	} else if (name == "s") {
		name = "south";
	} else if (name == "sw") {
		name = "southwest";
	} else if (name == "w") {
		name = "west";
	} else if (name == "nw") {
		name = "northwest";
	} else if (name == "u") {
		name = "up";
	} else if (name == "d") {
		name = "down";
	}

	return name;
}

std::string Room::describe() { 
	std::ostringstream os;
	std::string items = this->itemContainer.describe();
	os << this->description;
	if(items != "") {
		os << std::endl << this->itemContainer.describe();
	}

	os << std::endl << "Exits: ";
	auto it = this->exits.begin();
	os << it->first;
	it++;
	while(it != this->exits.end()) {
		os << ", " << it->first;
		it++;
	}

	return os.str();
}

void Room::setDescription(std::string _description) { 
	this->description = _description;
}

ItemContainer& Room::getItemContainer() {
	return this->itemContainer;
}