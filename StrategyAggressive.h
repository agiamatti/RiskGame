#pragma once
#include "Strategy.h"


class StrategyAggressive : public Strategy {
public:
    StrategyAggressive(Player* inputPlayer);
    void reinforceAtStart(int x);
    void reinforce();
    void attack();
    void fortify();
    int getDice(int max);
    bool isHumanStrategy();

};
