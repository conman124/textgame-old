#pragma once

#include <list>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "item.h"
#include "traits/describable.h"

class ItemContainer : public Describable {
	public:
		ItemContainer();
		std::string describe();
		void addItem(std::shared_ptr<Item> item);
	private:
		std::list<std::shared_ptr<Item>> items;

		std::unordered_map<std::type_index, size_t> getGroupedItemCounts();
};