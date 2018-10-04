#include <string>
#include <sstream>

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

std::string Item::getPluralNameWithCount(size_t count) {
	if(count == 1) {
		return "a " + this->getName();
	} else {
		std::ostringstream os;
		os << count << " ";
		os << this->getPluralName();
		return os.str();
	}
}

std::string Item::getPluralName() {
	return this->name + "s";
}