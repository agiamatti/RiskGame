#pragma once

class Player;
class Strategy {
public:

    virtual void attack() = 0;
    virtual void fortify() = 0;
    virtual void reinforce() = 0;
    //virtual ~Strategy()=0;  //no destructor needed as no data is owned by the strategy and the player is hanedled by the UI

protected:
    Player* player;
};
