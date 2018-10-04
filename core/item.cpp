#include <string>

#include "item.h"

Item::Item(std::string _name)
	: name(_name)
{

}

std::string Item::getName() {
	return this->name;
}

std::string Item::getShortName() {
	return this->name;
}