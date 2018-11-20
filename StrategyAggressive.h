#pragma once
#include <iostream>
#include "Strategy.h"
using namespace std;

class StrategyAggressive : public Strategy {
public:
    StrategyAggressive(Player* inputPlayer);
    void attack();
    void reinforce();
    void fortify();
    bool isHumanStrategy();

};
