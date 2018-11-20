#pragma once
#include <iostream>
#include "Strategy.h"
using namespace std;

class StrategyBenevolent : public Strategy {
public:
    StrategyBenevolent(Player* inputPlayer);
    //~StrategyBenevolent();
    void attack();
    void reinforce();
    void fortify();
};
