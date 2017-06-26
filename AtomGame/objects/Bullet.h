//
// Created by sl on 19.06.17.
//

#ifndef ATOMGAME_BULLET_H
#define ATOMGAME_BULLET_H

#include "PhysicalObject.h"

class Bullet : public PhysicalObject
{
public:
    Bullet(int x, int y, int sizeX, int sizeY, int damage, int _lifeTime);

    PhysicalObject::BlockType getClass() const;

    int getDamage() const;

    PhysicalObject::Direction getDirection();

    void setX(int x);

    void setY(int y);

    virtual Position tick ();

    bool isDestroyed();
protected:
    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

private:
    int _lifeTime;
    int _curTime;
    int _damage;
};


#endif //ATOMGAME_BULLET_H
