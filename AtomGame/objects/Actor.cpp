//
// Created by sl on 21.04.17.
//

#include "Actor.h"

Actor::Actor (int x, int y, int sizex, int sizey) : PhysicalObject (x, y, sizex, sizey), _onGround (true), _dx(0), _dy(0)
{

}

bool Actor::isOnGround () const
{
    return _onGround;
}

bool Actor::setOnGround (bool onGround)
{
    _onGround = onGround;
    return _onGround;
}

PhysicalObject::Position Actor::tick ()
{
    PhysicalObject::Position pos = PhysicalObject::tick ();
    pos.x += _dx;
    pos.y += _dy;
    _dx = 0;
    _dy = 0;
    return pos;
}

void Actor::setDx (int dx)
{
    _dx = dx;
}

void Actor::setDy (int dy)
{
    _dy = dy;
}

PhysicalObject::Direction Actor::getXDirection () const
{
    return (_vx + _dx)>0?Right:((_vx+_dx)<0?Left:No);
}

PhysicalObject::Direction Actor::getYDirection () const
{
    return (_vy + _dy)>0?Up:((_vy+_dy)<0?Down:No);
}
