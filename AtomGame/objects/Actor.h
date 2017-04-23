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

    Actor(int x, int y): x_(x), y_(y)
    {}

    void Move( int dx, int dy );

    //virtual void Jump() = 0;

    //virtual void Attack() = 0;

//    void setX(int x) { x_ = x; }
//    void setY(int y) { y_ = y; }
    int getX() { return x_; }
    int getY() { return y_; }

protected:
    int y_;
    int x_;
};


#endif //ATOMGAME_ACTOR_H
