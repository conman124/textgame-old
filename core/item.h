#pragma once

#include <string>

#include "traits/has_name.h"

class Item : public HasName {
	public:
		Item(std::string name);
		std::string getName();
		std::string getShortName();
		std::string getPluralNameWithCount(size_t count);
		std::string getPluralName();
	private:
		std::string name;
};