#pragma once
#include <iostream>
#include "Strategy.h"
using namespace std;

class StrategyHuman :public Strategy {
public:
    StrategyHuman(Player* inputPlayer);
    void attack();
    void reinforce();
    void fortify();
    bool isHumanStrategy();
};
