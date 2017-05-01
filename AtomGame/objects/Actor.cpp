//
// Created by sl on 21.04.17.
//

#include "Actor.h"

Actor::Actor (int x, int y, int sizex, int sizey) : PhysicalObject (x, y, sizex, sizey), _action (NoAction),
                                                    lookDirection (Right),
                                                    moving (false)
{

}

bool Actor::isOnGround () const
{
    return _blockedY == Down;
}

PhysicalObject::Position Actor::tick ()
{
    if (_vx != 0 && _dx != 0 && (_dx > 0 == _vx < 0))
        _vx += _dx > 0 ? 1 : -1;
    if (_vy != 0 && _dy != 0 && (_dy > 0 == _vy < 0))
        _vy += _dy > 0 ? 1 : -1;

    return PhysicalObject::tick ();
}

void Actor::collided (PhysicalObject &source, PhysicalObject::Axis relativeLocation)
{
    if (relativeLocation == axisX)
    {
        if (source.getX () < _x)
        {
            minDX.first = true;
            minDX.second = source.getVx ();
        } else
        {
            maxDX.first = true;
            maxDX.second = source.getVx ();
        }
    } else
    {
        if (source.getY () < _y)
        {
            minDY.first = true;
            minDY.second = source.getVy ();
        } else
        {
            maxDY.first = true;
            maxDY.second = source.getVy ();
        }
    }
}

void Actor::setAction(Action action) {
    _action = action;
}

Actor::Action Actor::getAction() const {
    return _action;
}

PhysicalObject::Direction Actor::getLookDirection () const
{
    return lookDirection;
}

void Actor::setLookDirection (PhysicalObject::Direction direction)
{
    lookDirection = direction;
}

bool Actor::isMoving ()
{
    return moving;
}

void Actor::setMoving (bool moving)
{
    Actor::moving = moving;
}
