#include <string>

#include "item.h"

Item::Item(std::string _description)
	: description(_description)
{

}

std::string Item::describe() {
	return this->description;
}