#pragma once

#include <string>

class HasName {
    public:
    virtual std::string getName() = 0;
	virtual std::string getShortName() = 0;
	virtual std::string getPluralName() = 0;
	virtual std::string getPluralNameWithCount(size_t count) = 0;
	virtual ~HasName() {};
};