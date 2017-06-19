//
// Created by sl on 19.06.17.
//

#include "Weapon.h"

Bullet *Weapon::tryShoot() {
    if (isOnCoolDown())
        return nullptr;
    Bullet *b =  new Bullet(0, 0, 5, 5, _damage);
    b->setVelocity(10, 0);
    _steps = 0;
    return b;
}

bool Weapon::isOnCoolDown() const
{
    return _steps < _coolDownTime;
}

void Weapon::tick()
{
    if (_steps<_coolDownTime)
        _steps++;
}

Weapon::Weapon(int damage, int coolDownTime) :_damage(damage), _coolDownTime(coolDownTime), _steps(coolDownTime)
{}
