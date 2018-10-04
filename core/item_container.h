#pragma once

#include <list>
#include <memory>
#include <unordered_map>
#include <typeindex>

#include "item.h"
#include "traits/describable.h"

class ItemContainerFormatter {
	friend class ItemContainer;
	public:
		virtual ~ItemContainerFormatter() {}
	protected:
		virtual std::string formatOneItem(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts) = 0;
		virtual std::string formatTwoItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts) = 0;
		virtual std::string formatManyItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts) = 0;
};

class ItemContainer : public Describable {
	public:
		ItemContainer(std::unique_ptr<ItemContainerFormatter> formatter);
		std::string describe();
		void addItem(std::shared_ptr<Item> item);
		bool contains(std::string itemName);
		void moveItemsInto(std::string itemName, ItemContainer& other);
	private:
		std::list<std::list<std::shared_ptr<Item>>::iterator> retrieveItems(std::string itemName);
		std::unordered_map<std::type_index, size_t> getGroupedItemCounts();

		std::list<std::shared_ptr<Item>> items;
		std::unique_ptr<ItemContainerFormatter> formatter;
};

// TODO think of a better way to do the formatters, because there's a decent amount of shared code, both between the
// methods and between the two formatters.
class RoomItemContainerFormatter : public ItemContainerFormatter {
	protected:
		std::string formatOneItem(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
		std::string formatTwoItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
		std::string formatManyItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
};

class InventoryItemContainerFormatter : public ItemContainerFormatter {
	protected:
		std::string formatOneItem(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
		std::string formatTwoItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
		std::string formatManyItems(std::list<std::shared_ptr<Item>>& items, std::unordered_map<std::type_index, size_t>& counts);
};