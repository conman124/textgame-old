#pragma once

#include <string>

#include "../traits/describable.h"

class Item : public Describable {
	public:
		Item(std::string description);
		std::string describe();
	private:
		std::string description;
};