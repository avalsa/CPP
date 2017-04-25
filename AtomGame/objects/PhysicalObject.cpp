//
// Created by svuatoslav on 4/25/17.
//

#include <cstdlib>
#include "PhysicalObject.h"

PhysicalObject::PhysicalObject (int x, int y, int sizex, int sizey) : _x (x), _y (y), _sizex (sizex), _sizey (sizey),
                                                                      _vx (0), _vy (0), _ax (0), _ay (0)
{
}

void PhysicalObject::move (Position position)
{
    _x = position.x;
    _y = position.y;
}

void PhysicalObject::setVelocity (int vx, int vy)
{
    _vx = vx;
    _vy = vy;
}

void PhysicalObject::setAcceleration (int ax, int ay)
{
    _ax = ax;
    _ay = ay;
}

PhysicalObject::Position PhysicalObject::tick ()
{
    if (abs (_vx += _ax) > maxSpeed)
        _vx = _vx > 0 ? maxSpeed : -maxSpeed;
    if (abs (_vy += _ay) > maxSpeed)
        _vy = _vy > 0 ? maxSpeed : -maxSpeed;

    return PhysicalObject::Position (_x + _vx, _y + _vy);
}

int PhysicalObject::getX () const
{
    return _x;
}

int PhysicalObject::getY () const
{
    return _y;
}

int PhysicalObject::getVx () const
{
    return _vx;
}

int PhysicalObject::getVy () const
{
    return _vy;
}

int PhysicalObject::getSizex () const
{
    return _sizex;
}

int PhysicalObject::getSizey () const
{
    return _sizey;
}

int PhysicalObject::getAx () const
{
    return _ax;
}

int PhysicalObject::getAy () const
{
    return _ay;
}

PhysicalObject::Position::Position (int x, int y) : x (x), y (y)
{
}
