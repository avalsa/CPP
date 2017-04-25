//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_ACTOR_H
#define ATOMGAME_ACTOR_H

#include "Weapon.h"
#include "PhysicalObject.h"

class Actor : public PhysicalObject
{
public:

    Actor (int x, int y, int sizex, int sizey);

    //virtual void jump() = 0;

    //virtual void attack() = 0;

//    void setX(int x) { x_ = x; }
//    void setY(int y) { y_ = y; }
};


#endif //ATOMGAME_ACTOR_H
