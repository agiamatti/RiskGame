#pragma once
#include "Strategy.h"

class StrategyBenevolent : public Strategy {
public:
    StrategyBenevolent(Player* inputPlayer);
    void reinforceAtStart(int x);
    void reinforce();
    void attack();
    void fortify();
    int getDice(int max);
    bool isHumanStrategy();
};
