//
// Created by sl on 06.04.17.
//

#include "Player.h"
#include "Teleporter.h"

Player::Player (int x, int y, int sizeX, int sizeY) :
        Actor (x, y, sizeX, sizeY),
        PhysicalObject(x, y, sizeX, sizeY, BlockType::Player),
        _respX (x), _respY (y), _coins(0), weapon(10, 10), _lastLive(0), _lives(5)
{}

void Player::respawn ()
{
    if(_lives)
    {
        --_lives;
        _alive = true;
        _x = _respX;
        _y = _respY;
    }
}

void Player::collided (const PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{
    switch (source->type ())
    {
        case PhysicalObject::BlockType::Bot:
            _alive = false;
            break;
        case PhysicalObject::BlockType::Respawn :
            _respX = _x;
            _respY = _y;
            Actor::collided (source, relativeLocation);
            break;
        case PhysicalObject::BlockType::MapChange :
            if (source->getClass () == MapChange)
            {
                _x = dynamic_cast<Teleporter*>(const_cast<PhysicalObject *>(source))->getDestX ();
                _y = dynamic_cast<Teleporter*>(const_cast<PhysicalObject *>(source))->getDestY ();
            } else
                logger.warn ("Block type mismatch encountered");
            break;
        case PhysicalObject::BlockType::Coin:
            _coins++;
            if (_coins / ((_lastLive+1)*100))
            {
                ++_lives;
                ++_lastLive;
            }
            break;
        default:
            Actor::collided (source, relativeLocation);
            break;
    }
}

PhysicalObject::BlockType Player::getClass () const
{
    return PhysicalObject::BlockType::Player;
}

int Player::getScore() {
    return _coins;
}

PhysicalObject::Position Player::tick() {
    weapon.tick();
    return Actor::tick();
}

PhysicalObject* Player::tryShoot()
{
    auto bullet = weapon.tryShoot();
    if (!bullet)
        return nullptr;
    bullet->setVelocity(getLookDirection() == PhysicalObject::Direction::Right
                        ? std::abs(bullet->getVx()) : -std::abs(bullet->getVx()), bullet->getVy());
    bullet->setY(_y + _sizeY / 3);
    if (_lookDirection == Right)
        bullet->setX(_x + _sizeX + 6);
    else
        bullet->setX(_x - bullet->getSizeX() - 6);
    return bullet;
}

int Player::getLives ()
{
    return _lives;
}
