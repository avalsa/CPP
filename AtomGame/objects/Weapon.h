//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_WEAPON_H
#define ATOMGAME_WEAPON_H

#include "GameObject.h"

class Weapon : public GameObject
{
public:
    Weapon(int damage) : damage_(damage), attackFrequency_(1), distance_to_start_attack_(1)
    {}

private:
    int damage_;
    int attackFrequency_;
    int distance_to_start_attack_;
};

#endif //ATOMGAME_WEAPON_H
