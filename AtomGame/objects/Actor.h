//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_ACTOR_H
#define ATOMGAME_ACTOR_H

#include "PhysicalObject.h"

class Actor : virtual public PhysicalObject
{
public:

    enum Action
    {
        Cover, Shoot, Interact, NoAction
    };

    Action getAction () const;

    void setAction (Action action);

    Actor (int x, int y, int sizeX, int sizeY);

    void setSize(int x, int y);

    bool isOnGround () const;

    virtual PhysicalObject::Position tick ();

    bool isMoving () const;

    PhysicalObject::Direction getLookDirection () const;

    void setLookDirection (Direction direction);

    bool isAlive() const;

    void setMoving (bool moving);

    //virtual void attack() = 0;

protected:

    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

    bool _alive;

    Action _action;

    Direction _lookDirection;

    bool _moving;

};


#endif //ATOMGAME_ACTOR_H
