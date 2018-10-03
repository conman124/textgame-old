#pragma once

#include <string>

class Describable {
    public:
    virtual std::string describe() = 0;
	virtual ~Describable() {};
};