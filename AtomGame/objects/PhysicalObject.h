#ifndef ATOMGAME_PHYSICALOBJECT_H
#define ATOMGAME_PHYSICALOBJECT_H

#include <log4cpp/Category.hh>
#include <typeinfo>
#include <unordered_map>
#include <tinyxml2.h>

class PhysicalObject
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
    enum BlockType
    {
        Solid, Deadly, Respawn, Portal, MapChange, Player, Coin, Bot, Bullet
    };

    struct Position;

    PhysicalObject (int x, int y, int sizeX, int sizeY, BlockType type = Solid);

    void move (Position position);

    void setVelocity (int vx, int vy);

    void setAcceleration (int ax, int ay);

    virtual Position tick ();

    virtual ~PhysicalObject();

    int getX () const;

    int getY () const;

    int getVx () const;

    int getVy () const;

    int getSizeX () const;

    int getSizeY () const;

    int getAx () const;

    int getAy () const;

    void addDx (int _dx);

    void addDy (int _dy);

    void addCollision (PhysicalObject *source, Axis relativeLocation);

    void processCollisions ();

    BlockType type () const;

    virtual BlockType getClass () const;

protected:
    int _x;
    int _y;
    int _vx;
    int _vy;
    int _sizeX;
    int _sizeY;
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
    Direction _newBlockedX;
    Direction _newBlockedY;
    static log4cpp::Category &logger;

    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

    void setType (const BlockType type);

private:
    std::unordered_map<PhysicalObject *, PhysicalObject::Axis> collisions;
    BlockType _type;

};

struct PhysicalObject::Position
{
    int x;
    int y;

    Position (int x = 0, int y = 0);
};

#endif //ATOMGAME_PHYSICALOBJECT_H
