//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_BOT_H
#define ATOMGAME_BOT_H


#include "Actor.h"

class Bot : public Actor
{
    Bot(int x, int y, int hp, int hp_max, Weapon weapon) : Actor(x, y, hp_max, hp_max, weapon)
    {}
};


#endif //ATOMGAME_BOT_H
