//
// Created by sl on 19.06.17.
//

#ifndef ATOMGAME_BULLET_H
#define ATOMGAME_BULLET_H

#include "PhysicalObject.h"

class Bullet : public PhysicalObject
{
public:
    Bullet(int x, int y, int sizeX, int sizeY, int damage);

    PhysicalObject::BlockType getClass() const;

    int getDamage() const;

    PhysicalObject::Direction getDirection();

    void setX(int x);

    void setY(int y);

protected:
    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

private:
    int _damage;
};


#endif //ATOMGAME_BULLET_H
