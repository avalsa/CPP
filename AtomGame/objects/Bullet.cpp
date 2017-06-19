//
// Created by sl on 19.06.17.
//

#include "Bullet.h"


Bullet::Bullet(int x, int y, int sizeX, int sizeY, int damage):
        PhysicalObject(x, y, sizeX, sizeY, PhysicalObject::BlockType::Bullet), _damage(damage)
{}

PhysicalObject::BlockType Bullet::getClass() const {
    return PhysicalObject::BlockType::Bullet;
}

void Bullet::collided(const PhysicalObject *source, PhysicalObject::Axis relativeLocation) {
    PhysicalObject::collided(source, relativeLocation);
}

int Bullet::getDamage() const {
    return _damage;
}

PhysicalObject::Direction Bullet::getDirection() {
    return _vx > 0 ? PhysicalObject::Direction::Right : PhysicalObject::Direction::Left;
}

void Bullet::setX(int x)
{
    _x = x;
}

void Bullet::setY(int y)
{
    _y = y;
}
