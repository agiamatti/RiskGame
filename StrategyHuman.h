#pragma once
#include "Strategy.h"

class StrategyHuman :public Strategy {
public:
    StrategyHuman(Player* inputPlayer);
    void reinforceAtStart(int x);
    void reinforce();
    void attack();
    void fortify();
    int getDice(int max);
    bool isHumanStrategy();
};
