#pragma once
#include <iostream>
using namespace std;

class Player;
class Strategy {
public:

    virtual void reinforceAtStart(int x)=0;
    virtual void reinforce() = 0;
    virtual void attack() = 0;
    virtual void fortify() = 0;
    virtual int getDice(int max)=0;
    virtual bool isHumanStrategy()=0;
    //virtual ~Strategy()=0;  //no destructor needed as no data is owned by the strategy and the player is handled by the UI

protected:
    Player* player;
};
