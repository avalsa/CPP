#include "PhysicalObject.h"

log4cpp::Category &PhysicalObject::logger = log4cpp::Category::getInstance (typeid (PhysicalObject).name ());


PhysicalObject::PhysicalObject (int x, int y, int sizeX, int sizeY, BlockType type) : _x (x), _y (y), _sizeX (sizeX),
                                                                                      _sizeY (sizeY),
                                                                                      _vx (0), _vy (0), _ax (0), _ay (0),
                                                                                      _blockedX (NoDirection), _blockedY (NoDirection),
                                                                                      _dx (0), _dy (0), minDX (false, 0),
                                                                                      maxDX (false, 0),
                                                                                      minDY (false, 0),
                                                                                      maxDY (false, 0), _type (type)
{
}

void PhysicalObject::move (Position position)
{
    if (abs (_vx + _dx) > abs (_x - position.x))
    {
        PhysicalObject::Direction newBlocked = (_x + _vx + _dx) > position.x ? Right : Left;
        if (_blockedX == newBlocked)
        {
            int nvx = position.x - _x - _dx;
            if(_vx > 0 == nvx > 0 || nvx == 0)
                _vx = nvx;
            else
                _vx = 0;
        }
    } else
        _blockedX = NoDirection;
    if (abs (_vy + _dy) != abs (_y - position.y))
    {
        PhysicalObject::Direction newBlocked = (_y + _vy + _dy) > position.y ? Down : Up;
        if (_blockedY == newBlocked)
        {
            int nvy = position.y - _y - _dy;
            if(_vy > 0 == nvy > 0 || nvy == 0)
                _vy = nvy;
            else
                _vy = 0;
        }
        _blockedY = newBlocked;
    } else
        _blockedY = NoDirection;
    _x = position.x;
    _y = position.y;
    _dx = 0;
    _dy = 0;
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

int PhysicalObject::getSizeX () const
{
    return _sizeX;
}

int PhysicalObject::getSizeY () const
{
    return _sizeY;
}

int PhysicalObject::getAx () const
{
    return _ax;
}

int PhysicalObject::getAy () const
{
    return _ay;
}

void PhysicalObject::collided (const PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{

}

void PhysicalObject::addCollision (PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{
    if (collisions.find (source) != collisions.end ())
        return;
    collisions.insert (std::pair<PhysicalObject *, Axis> (source, relativeLocation));
}

void PhysicalObject::processCollisions ()
{
    for (std::unordered_map<PhysicalObject *, Axis>::const_iterator i = collisions.cbegin ();
         i != collisions.cend (); ++i)
        collided (i->first, i->second);
    collisions.clear ();
}

PhysicalObject::BlockType PhysicalObject::type () const
{
    return _type;
}

PhysicalObject::BlockType PhysicalObject::getClass () const
{
    return Solid;
}

void PhysicalObject::setType (const PhysicalObject::BlockType type)
{
    _type = type;
}

PhysicalObject::~PhysicalObject()
{}

PhysicalObject::Position::Position (int x, int y) : x (x), y (y)
{
}
