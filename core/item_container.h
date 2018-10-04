#pragma once

#include <list>
#include <memory>

#include "item.h"
#include "traits/describable.h"

class ItemContainer : public Describable {
	public:
		ItemContainer();
		std::string describe();
		void addItem(std::shared_ptr<Item> item);

	private:
		std::list<std::shared_ptr<Item>> items;
};