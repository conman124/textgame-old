#pragma once

#include <string>

#include "traits/has_name.h"

class Item : public HasName {
	public:
		Item(std::string name);
		std::string getName();
		std::string getShortName();
	private:
		std::string name;
};