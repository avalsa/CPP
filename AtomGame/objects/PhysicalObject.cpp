//
// Created by svuatoslav on 4/25/17.
//

#include <cstdlib>
#include "PhysicalObject.h"

log4cpp::Category &PhysicalObject::logger = log4cpp::Category::getInstance (typeid (PhysicalObject).name ());


PhysicalObject::PhysicalObject (int x, int y, int sizex, int sizey) : _x (x), _y (y), _sizex (sizex), _sizey (sizey),
                                                                      _vx (0), _vy (0), _ax (0), _ay (0),
                                                                      _blockedX (NoDirection), _blockedY (NoDirection),
                                                                      _dx (0), _dy (0), minDX (false, 0),
                                                                      maxDX (false, 0),
                                                                      minDY (false, 0), maxDY (false, 0)
{
}

void PhysicalObject::move (Position position)
{
    if (abs (_vx) > abs (_x - position.x))
    {
        int prevvx = _vx;
        if (_blockedX != NoDirection && (_vx > 0) != (_x > position.x))
            _vx = position.x - _x;
        _blockedX = (_x + prevvx) > position.x ? Right : Left;
    } else
        _blockedX = NoDirection;
    if (abs (_vy) > abs (_y - position.y))
    {
        int prevvy = _vy;
        if (_blockedY != NoDirection && (_vy > 0) != (_y > position.y))
            _vy = position.y - _y;
        _blockedY = (_y + prevvy) > position.y ? Down : Up;
    } else
        _blockedY = NoDirection;
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

void PhysicalObject::addDx (int dx)
{
    _dx += dx;
}

void PhysicalObject::addDy (int dy)
{
    _dy += dy;
}

PhysicalObject::Position PhysicalObject::tick ()
{
    if (abs (_vx += _ax) > maxSpeed)
        _vx = _vx > 0 ? maxSpeed : -maxSpeed;
    if (abs (_vy += _ay) > maxSpeed)
        _vy = _vy > 0 ? maxSpeed : -maxSpeed;
    int cx = _dx + _vx, cy = _dy + _vy;

    if (minDX.first)
    {
        if (cx < minDX.second)
            cx = minDX.second;
        minDX.first = false;
    }
    if (maxDX.first)
    {
        if (cx > maxDX.second)
            cx = maxDX.second;
        maxDX.first = false;
    }
    if (minDY.first)
    {
        if (cy < minDY.second)
            cy = minDY.second;
        minDY.first = false;
    }
    if (maxDY.first)
    {
        if (cy > maxDY.second)
            cy = maxDY.second;
        maxDY.first = false;
    }
    PhysicalObject::Position ret (_x + cx, _y + cy);

    _dx = 0;
    _dy = 0;

    return ret;
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

void PhysicalObject::collided (PhysicalObject &source, PhysicalObject::Axis relativeLocation)
{
    if (relativeLocation == axisX)
        source.addDy (_vy);
    else
        source.addDx (_vx);
}

void PhysicalObject::addCollision (PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{
    for (std::vector<std::pair<PhysicalObject *, Axis>>::const_iterator i = collisions.cbegin ();
         i != collisions.cend (); ++i)
        if (i->first == source)
            return;
    collisions.push_back (std::pair<PhysicalObject *, Axis> (source, relativeLocation));
}

void PhysicalObject::processCollisions ()
{
    //todo Replace with map for better search
    for (std::vector<std::pair<PhysicalObject *, Axis>>::const_iterator i = collisions.cbegin ();
         i != collisions.cend (); ++i)
        collided (*(*i).first, (*i).second);
    collisions.clear ();
}

PhysicalObject::Position::Position (int x, int y) : x (x), y (y)
{
}
