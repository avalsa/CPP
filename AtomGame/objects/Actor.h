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

    enum Action
    {
        Jump, Cover, Shoot, Interact, NoAction, Move
    };

    Action getAction() const;

    void setAction(Action action);

    void setDx (int _dx);

    void setDy (int _dy);

    Actor (int x, int y, int sizex, int sizey);

    bool isOnGround() const;

    bool setOnGround(bool onGround);

    virtual PhysicalObject::Position tick ();

    PhysicalObject::Direction getXDirection() const;

    PhysicalObject::Direction getYDirection() const;

    //virtual void jump() = 0;

    //virtual void attack() = 0;

//    void setX(int x) { x_ = x; }
//    void setY(int y) { y_ = y; }

private:

    bool _onGround;
    Action _action;

protected:

    int _dx;

    int _dy;


};


#endif //ATOMGAME_ACTOR_H
