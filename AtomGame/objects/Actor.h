//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_ACTOR_H
#define ATOMGAME_ACTOR_H

#include "GameObject.h"
#include "Weapon.h"
class Actor : public GameObject
{
public:

    enum Direction { Up, Down, Left, Right};

    Actor(int x, int y, int hp_max, int hp_cur, Weapon weapon): x_(x), y_(y), hp_max_(hp_max), hp_cur_(hp_cur), weapon_(weapon), direction_(Direction::Right)
    {}

    virtual void Move() = 0;

    virtual void Jump() = 0;

    virtual void Attack() = 0;

private:
    int x_;
    int y_;
    int hp_max_;
    int hp_cur_;
    Weapon weapon_;
    Direction direction_;
};

#endif //ATOMGAME_ACTOR_H
