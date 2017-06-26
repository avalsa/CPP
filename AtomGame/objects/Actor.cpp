//
// Created by sl on 21.04.17.
//

#include "Actor.h"
#include "Teleporter.h"

Actor::Actor (int x, int y, int sizeX, int sizeY) : PhysicalObject (x, y, sizeX, sizeY, Player), _action (NoAction),
                                                    _lookDirection (Right),
                                                    _moving (false),
                                                    _alive(true)
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

void Actor::collided (const PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{
    switch (source->type ())
    {
        case PhysicalObject::BlockType::Deadly :
            _alive = false;
            //respawn ();
            break;
        case PhysicalObject::BlockType::Bullet:
            _alive = false;
            //respawn ();
            break;
        case PhysicalObject::BlockType::Portal :
            if (source->getClass () == Portal || source->getClass () == MapChange)
            {
                _x = dynamic_cast<Teleporter*>(const_cast<PhysicalObject *>(source))->getDestX ();
                _y = dynamic_cast<Teleporter*>(const_cast<PhysicalObject *>(source))->getDestY ();
            } else
                logger.warn ("Block type mismatch encountered");
            break;
        default:
            if (relativeLocation == axisX)
            {
                if (source->getX () < _x)
                {
                    if (minDX.first)
                        minDX.second = std::max (minDX.second, source->getVx ());
                    else
                    {
                        minDX.first = true;
                        minDX.second = source->getVx ();
                    }
                } else
                {
                    if (maxDX.first)
                        maxDX.second = std::min (maxDX.second, source->getVx ());
                    else
                    {
                        maxDX.first = true;
                        maxDX.second = source->getVx ();
                    }
                }
                //_dy += source.getVy ();
            } else
            {
                if (source->getY () < _y)
                {
                    if (minDY.first)
                        minDY.second = std::max (minDY.second, source->getVy ());
                    else
                    {
                        minDY.first = true;
                        minDY.second = source->getVy ();
                    }
                } else
                {
                    if (maxDY.first)
                        maxDY.second = std::min (maxDY.second, source->getVy ());
                    else
                    {
                        maxDY.first = true;
                        maxDY.second = source->getVy ();
                    }
                }
                _dx += source->getVx ();
            }
            break;
    }
}

void Actor::setAction (Action action)
{
    _action = action;
}

Actor::Action Actor::getAction () const
{
    return _action;
}

PhysicalObject::Direction Actor::getLookDirection () const
{
    return _lookDirection;
}

void Actor::setLookDirection (PhysicalObject::Direction direction)
{
    _lookDirection = direction;
}

bool Actor::isMoving () const
{
    return _moving;
}

void Actor::setMoving (bool moving)
{
    _moving = moving;
}

bool Actor::isAlive() const {
    return _alive;
}

void Actor::setSize(int x, int y) {
    _sizeX = x; _sizeY = y;
}
