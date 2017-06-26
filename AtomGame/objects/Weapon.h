//
// Created by sl on 19.06.17.
//

#ifndef ATOMGAME_WEAPON_H
#define ATOMGAME_WEAPON_H

#include "Bullet.h"

class Weapon
{
public:

    Weapon(int damage, int coolDownTime);

    Bullet* tryShoot();

    void tick();

    bool isOnCoolDown() const;

private:
    int _steps;
    int _damage;
    int _coolDownTime;
};


#endif //ATOMGAME_WEAPON_H
