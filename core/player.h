#pragma once

#include "creature.h"

class Driver;

class Player : public Creature {
    public:
        Player(Driver& driver);
};