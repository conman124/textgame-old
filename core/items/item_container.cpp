#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <sstream>

#include "item.h"
#include "item_container.h"

ItemContainer::ItemContainer()
	: items()
{

}

std::string ItemContainer::describe() {
	std::ostringstream os;
	if(this->items.size() == 0) {
		return "";
	} else if(this->items.size() == 1) {
		os << "There is " << this->items.front()->describe() << " here.";
	} else if(this->items.size() == 2) {
		auto it = this->items.begin();
		os << "There are ";
		os << (*it)->describe();
		os << " and ";
		it++;
		os << (*it)->describe();
		os << " here.";
	} else {
		auto it = this->items.begin();
		os << "There are ";
		for(size_t i = 0; i < this->items.size(); i++) {
			if(i == this->items.size() - 1) {
				os << "and ";
			}
			os << (*it)->describe();
			if(i != this->items.size() - 1) {
				os << ", ";
			}
			it++;
		}
		os << " here.";
	}

	return os.str();
}

void ItemContainer::addItem(std::shared_ptr<Item> item) {
	this->items.push_back(item);
}