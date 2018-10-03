#include <algorithm>
#include <iostream>
#include <string>

#include "room.h"

template <class T>
bool operator==(const std::weak_ptr<T> weak, std::nullptr_t);

// https://stackoverflow.com/a/45507610/1205493
// Checks if a weak pointer is empty
template <class T>
bool operator==(const std::weak_ptr<T> weak, std::nullptr_t) {
    using wt = std::weak_ptr<T>;
    return !weak.owner_before(wt{}) && !wt{}.owner_before(weak);
}

Room::Room(Driver& _driver)
    : creatures()
	, description("")
	, driver(_driver)
    , exits()
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
    return (this->exits[name] == nullptr) ? nullptr : this->exits[name].lock();
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

std::string Room::getDescription() { 
	return this->description;
}

void Room::setDescription(std::string _description) { 
	this->description = _description;
}