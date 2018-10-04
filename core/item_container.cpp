#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <sstream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>

#include "item.h"
#include "item_container.h"

ItemContainer::ItemContainer()
	: items()
{

}

std::string ItemContainer::describe() {
	std::ostringstream os;
	auto counts = this->getGroupedItemCounts();

	switch(counts.size()) {
		case 0: return "";
		case 1: {
			os << "There ";
			if(counts.begin()->second > 1) {
				os << "are ";
			} else {
				os << "is ";
			}
			auto item = this->items.front();
			os << item->getPluralNameWithCount(counts[typeid(*item)]) << " here.";
			break;
		}
		case 2: {
			auto it = this->items.begin();
			std::type_index firstType(typeid(**it));

			os << "There are ";
			os << (*it)->getPluralNameWithCount(counts[typeid(**it)]);
			os << " and ";
			do {
				it++;
			} while(firstType == std::type_index(typeid(**it)));
			os << (*it)->getPluralNameWithCount(counts[typeid(**it)]);
			os << " here.";
			break;
		}
		default: {
			std::unordered_set<std::type_index> seen;
			auto it = this->items.begin();
			os << "There are ";
			for(size_t i = 0; i < counts.size(); i++) {
				while (seen.find(std::type_index(typeid(**it))) != seen.end()) {
					it++;
				}

				if(i == counts.size() - 1) {
					os << "and ";
				}
				os << (*it)->getPluralNameWithCount(counts[typeid(**it)]);
				if(i != counts.size() - 1) {
					os << ", ";
				}
				seen.insert(std::type_index(typeid(**it)));
			}
			os << " here.";
		}
	}

	return os.str();
}

void ItemContainer::addItem(std::shared_ptr<Item> item) {
	this->items.push_back(item);
}

bool ItemContainer::contains(std::string itemName) {
	return this->retrieveItems(itemName).size() > 0;
}

std::list<std::list<std::shared_ptr<Item>>::iterator> ItemContainer::retrieveItems(std::string itemName) {
	std::list<std::list<std::shared_ptr<Item>>::iterator> ret;

	for(auto it = this->items.begin(); it != this->items.end(); it++) {
		if((*it)->getPluralName() == itemName) {
			ret.push_back(it);
		}

		// Prefer singular name over a plural.  Hopefully, there's never any items that have the same plural
		// and singular as each other.
		if((*it)->getName() == itemName) {
			ret.clear();
			ret.push_back(it);
			return ret;
		}
	}

	return ret;
}

void ItemContainer::moveItemsInto(std::string itemName, ItemContainer& other) {
	auto itemsToMove = this->retrieveItems(itemName);

	for(auto item : itemsToMove) {
		other.addItem(*item);
		this->items.erase(item);
	}
}

std::unordered_map<std::type_index, size_t> ItemContainer::getGroupedItemCounts() {
	std::unordered_map<std::type_index, size_t> counts;

	for(auto item : this->items) {
		std::type_index index(typeid(*item));
		if(counts.find(index) == counts.end()) {
			counts[index] = 0;
		}
		counts[index]++;
	}

	return counts;
}