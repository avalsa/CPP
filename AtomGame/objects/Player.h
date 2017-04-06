//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_PLAYER_H
#define ATOMGAME_PLAYER_H


#include "Actor.h"

class Player : public Actor
{
public:
    Player(int x, int y, int hp, int hp_max, Weapon weapon) : Actor(x, y, hp_max, hp_max, weapon)
    {}
};


#endif //ATOMGAME_PLAYER_H
