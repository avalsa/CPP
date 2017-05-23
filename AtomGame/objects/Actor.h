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
        Cover, Shoot, Interact, NoAction
    };

    Action getAction () const;

    void setAction (Action action);

    Actor (int x, int y, int sizeX, int sizeY);

    bool isOnGround () const;

    virtual PhysicalObject::Position tick ();

    bool isMoving ();

    PhysicalObject::Direction getLookDirection () const;

    void setLookDirection (Direction direction);

    //virtual void attack() = 0;

protected:

    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

private:

    Action _action;

    Direction lookDirection;

    bool moving;

public:
    void setMoving (bool moving);

};


#endif //ATOMGAME_ACTOR_H
