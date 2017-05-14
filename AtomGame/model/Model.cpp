//
// Created by sl on 06.04.17.
//

#include <memory>

#include "Model.h"

log4cpp::Category &Model::logger = log4cpp::Category::getInstance (typeid (Model).name ());

void Model::tick ()
{
    logger.info ("Model tick");
    for (std::vector<PhysicalObject *>::iterator i = objs.begin (); i != objs.end (); i++)
    {
        PhysicalObject::Position pos = (*i)->tick ();
        tryMove (**i, pos);
    }
    for (std::vector<PhysicalObject *>::iterator i = objs.begin (); i != objs.end (); i++)
    {
        (*i)->processCollisions ();
    }
}

void Model::startGame ()
{
    blocks.push_back (PhysicalObject (-1000, 11, 100000, 10));
    PhysicalObject wall (-400, -125, 100, 100);
    wall.setVelocity (1, 0);
    blocks.push_back (wall);
    PhysicalObject rock (-500, -24, 10, 10);
    rock.setVelocity (2, 0);
    blocks.push_back (rock);
    player.setAcceleration (0, gravity);
    for (std::vector<Bot>::iterator i = bots.begin (); i != bots.end (); ++i)
        objs.emplace_back (&(*i));
    for (std::vector<PhysicalObject>::iterator i = blocks.begin (); i != blocks.end (); ++i)
        objs.emplace_back (&(*i));
}

/*void Model::movePlayer(Actor::Direction direction) {
    if (direction==Actor::Direction::Right) player.move (1, 0);//todo add dependency on speed or smth more interesting
    if (direction==Actor::Direction::Left) player.move (-1, 0);
    if (direction==Actor::Direction::Up) player.move (0, 1);
    if (direction==Actor::Direction::Down) player.move (0, -1);
}*/

void Model::actPlayer (Actor::Action action) {}

bool Model::isPlayerWin ()
{
    return false;
}

Model::Model () : bots (), objs (), gameField (100, 100), player (0, -200, 38, 42)
{
    logger.info ("Model init");
    objs.emplace_back (&player);
}

const Player &Model::getPlayer () const
{
    return player;
}

const std::vector<Bot> &Model::getBots () const
{
    return bots;
}

const GameField &Model::getGameField () const
{
    return gameField;
}

const std::vector<PhysicalObject *> &Model::getObjs () const
{
    return objs;
}

const std::vector<PhysicalObject> &Model::getBlocks () const
{
    return blocks;
}

void Model::movePlayer (Actor::Direction direction)
{
    switch (direction)
    {
        case PhysicalObject::Direction::Up:
            if (player.isOnGround ())
            {
                player.setVelocity (player.getVx (), -jumpStrength);
            }
            break;
        case PhysicalObject::Direction::Right:
            player.addDx (playerMovementSpeed);
            player.setMoving (true);
            player.setLookDirection (PhysicalObject::Direction::Right);
            break;
        case PhysicalObject::Direction::Down:
            player.addDy (playerMovementSpeed);
            break;
        case PhysicalObject::Direction::Left:
            player.addDx (-playerMovementSpeed);
            player.setMoving (true);
            player.setLookDirection (PhysicalObject::Direction::Left);
            break;
        case PhysicalObject::Direction::NoDirection:
            player.setMoving (false);
            break;
        default:
            break;
    }
}

void Model::tryMove (PhysicalObject &obj, PhysicalObject::Position position)
{
    PhysicalObject::Position ret (position);
    std::vector<PhysicalObject *> collides;
    for (std::vector<PhysicalObject *>::iterator i = objs.begin (); i != objs.end (); i++)
    {
        if (*i != &obj)
        {
            std::pair<bool, int> xPos = collidesOnX (obj, **i, position);
            if (xPos.first)
            {
                if (abs (xPos.second - obj.getX ()) < abs (ret.x - obj.getX ()))
                {
                    ret.x = xPos.second;
                    collides.clear ();
                    collides.push_back (*i);
                } else if (xPos.second == ret.x)
                    collides.push_back (*i);
            }
        }
    }
    for (std::vector<PhysicalObject *>::iterator i = collides.begin (); i != collides.end (); i++)
    {
        (*i)->addCollision (&obj, PhysicalObject::Axis::axisX);
        obj.addCollision (*i, PhysicalObject::Axis::axisX);
    }
    collides.clear ();
    for (std::vector<PhysicalObject *>::iterator i = objs.begin (); i != objs.end (); i++)
    {
        if (*i != &obj)
        {
            std::pair<bool, int> yPos = collidesOnY (obj, **i, position);
            if (yPos.first)
            {
                if (abs (yPos.second - obj.getY ()) < abs (ret.y - obj.getY ()))
                {
                    ret.y = yPos.second;
                    collides.clear ();
                    collides.push_back (*i);
                } else if (yPos.second == ret.y)
                    collides.push_back (*i);
            }
        }
    }
    for (std::vector<PhysicalObject *>::iterator i = collides.begin (); i != collides.end (); i++)
    {
        (*i)->addCollision (&obj, PhysicalObject::Axis::axisY);
        obj.addCollision (*i, PhysicalObject::Axis::axisY);
    }
    obj.move (ret);
}

std::pair<bool, int>
Model::collidesOnX (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos)
{
    int y11 = obj1.getY ();
    int y12 = y11 + obj1.getSizeY () - 1;
    int y21 = obj2.getY ();
    int y22 = y21 + obj2.getSizeY () - 1;
    int x11 = obj1.getX ();
    //int x12 = x11 + obj1.getSizeX () -1;
    int x21 = obj2.getX ();
    int x22 = x21 + obj2.getSizeX () - 1;
    std::pair<bool, int> ret (false, pos.x);
    if (y11 >= y21 && y11 <= y22 || y21 >= y11 && y21 <= y12)
    {
        if (x11 > x21)
        {
            if (ret.second <= x22 + 1)
            {
                ret.second = x22 + 1;
                ret.first = true;
            }
        } else
        {
            if (ret.second + obj1.getSizeX () >= x21)
            {
                ret.second = x21 - obj1.getSizeX ();
                ret.first = true;
            }
        }
    }
    return ret;
}

std::pair<bool, int>
Model::collidesOnY (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos)
{
    int y11 = obj1.getY ();
    //int y12 = y11 + obj1.getSizeY () -1;
    int y21 = obj2.getY ();
    int y22 = y21 + obj2.getSizeY () - 1;
    int x11 = obj1.getX ();
    int x12 = x11 + obj1.getSizeX () - 1;
    int x21 = obj2.getX ();
    int x22 = x21 + obj2.getSizeX () - 1;
    std::pair<bool, int> ret (false, pos.y);
    if (x11 >= x21 && x11 <= x22 || x21 >= x11 && x21 <= x12)
    {
        if (y11 > y21)
        {
            if (ret.second <= y22 + 1)
            {
                ret.second = y22 + 1;
                ret.first = true;
            }
        } else
        {
            if (ret.second + obj1.getSizeY () >= y21)
            {
                ret.second = y21 - obj1.getSizeY ();
                ret.first = true;
            }
        }
    }
    return ret;
}





