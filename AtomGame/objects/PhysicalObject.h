//
// Created by svuatoslav on 4/25/17.
//

#ifndef ATOMGAME_PHYSICALOBJECT_H
#define ATOMGAME_PHYSICALOBJECT_H

#include <log4cpp/Category.hh>
#include <typeinfo>
#include <unordered_map>
#include "GameObject.h"

class PhysicalObject : public GameObject
{
public:

    enum Direction
    {
        Up, Down, Left, Right, NoDirection
    };
    enum Axis
    {
        axisX, axisY
    };

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

    void addDx (int _dx);

    void addDy (int _dy);

    void addCollision (PhysicalObject *source, Axis relativeLocation);

    void processCollisions ();

protected:
    int _x;
    int _y;
    int _vx;
    int _vy;
    int _sizex;
    int _sizey;
    int _ax;
    int _ay;
    int _dx;
    int _dy;
    std::pair<bool, int> minDX;
    std::pair<bool, int> maxDX;
    std::pair<bool, int> minDY;
    std::pair<bool, int> maxDY;
    const int maxSpeed = 30;
    Direction _blockedX;
    Direction _blockedY;
    static log4cpp::Category &logger;

    virtual void collided (const PhysicalObject &source, Axis relativeLocation);

private:
    std::unordered_map<PhysicalObject *, PhysicalObject::Axis> collisions;

};

struct PhysicalObject::Position
{
    int x;
    int y;

    Position (int x = 0, int y = 0);
};

#endif //ATOMGAME_PHYSICALOBJECT_H
