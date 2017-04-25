//
// Created by svuatoslav on 4/25/17.
//

#ifndef ATOMGAME_PHYSICALOBJECT_H
#define ATOMGAME_PHYSICALOBJECT_H


#include <queue>
#include "GameObject.h"

class PhysicalObject : public GameObject
{
protected:
    int _x;
    int _y;
    int _vx;
    int _vy;
    int _sizex;
    int _sizey;
    int _ax;
    int _ay;
    const int maxSpeed = 30;
public:
    struct Position;

    PhysicalObject (int x, int y, int sizex, int sizey);

    void move (Position position);

    void setVelocity (int vx, int vy);

    void setAcceleration (int ax, int ay);

    virtual Position tick ();

    int getX () const;

    int getY () const;

    int getVx () const;

    int getVy () const;

    int getSizex () const;

    int getSizey () const;

    int getAx () const;

    int getAy () const;

    enum Direction
    {
        Up, Down, Left, Right
    };
    enum Actions
    {
        Jump, Cover, Shoot, Interact
    };
};

struct PhysicalObject::Position
{
    int x;
    int y;

    Position (int x, int y);
};


#endif //ATOMGAME_PHYSICALOBJECT_H
