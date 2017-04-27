//
// Created by sl on 06.04.17.
//

#include <memory>

#include "Model.h"

log4cpp::Category& Model::logger = log4cpp::Category::getInstance(typeid(Model).name());

void Model::tick(){
    logger.info("Model tick");
    PhysicalObject::Position pos = player.tick ();
    int prevX = pos.x;
    int prevY = pos.y;
    pos = canMove (&player, pos);
    if (player.setOnGround (prevY != pos.y))
        player.setVelocity (player.getVx (), 0);
    if (prevX != pos.x)
        player.setVelocity (0, player.getVy ());
    player.move (pos);
    for (std::vector<PhysicalObject>::iterator i = nonActiveObjs.begin (); i != nonActiveObjs.end (); i++)
    {
        pos = i->tick ();
        prevX = pos.x;
        prevY = pos.y;
        pos = canMove (&(*i), pos);
        if ((prevY != pos.y))
            i->setVelocity (player.getVx (), 0);
        if (prevX != pos.x)
            i->setVelocity (0, player.getVy ());
        i->move (pos);
    }
    for (std::vector<Bot>::iterator i = bots.begin (); i != bots.end (); i++)
    {
        pos = i->tick ();
        prevX = pos.x;
        prevY = pos.y;
        pos = canMove (&(*i), pos);
        if ((prevY != pos.y))
            i->setVelocity (player.getVx (), 0);
        if (prevX != pos.x)
            i->setVelocity (0, player.getVy ());
        i->move (pos);
    }
}

void Model::startGame() {
    nonActiveObjs.push_back (PhysicalObject (-10, -11, 1000, 10));
    nonActiveObjs.push_back (PhysicalObject (100, -10, 10, 100));
}

/*void Model::movePlayer(Actor::Direction direction) {
    if (direction==Actor::Direction::Right) player.move (1, 0);//todo add dependency on speed or smth more interesting
    if (direction==Actor::Direction::Left) player.move (-1, 0);
    if (direction==Actor::Direction::Up) player.move (0, 1);
    if (direction==Actor::Direction::Down) player.move (0, -1);
}*/

void Model::actPlayer (Actor::Actions action) {}

bool Model::isPlayerWin() {
    return false;
}

Model::Model () : player (0, 0, 10, 10), bots (), nonActiveObjs (), gameField (100, 100)
{
    logger.info("Model init");
    player.setAcceleration (0, -1);
}

const Player &Model::getPlayer() const {
    return player;
}

const std::vector<Bot> &Model::getBots() const {
    return bots;
}

const GameField &Model::getGameField() const {
    return gameField;
}

const std::vector<PhysicalObject> &Model::getNonActiveObjs () const
{
    return nonActiveObjs;
}

void Model::movePlayer (Actor::Direction direction)
{
    if (direction == PhysicalObject::Direction::Up)
    {
        if (player.isOnGround ())
            player.setVelocity (player.getAx (), 20);
    } else if (direction == PhysicalObject::Direction::Right)
        player.setDx (playerMovementSpeed);
    else if (direction == PhysicalObject::Direction::Down)
        player.setDy (-playerMovementSpeed);
    else if (direction == PhysicalObject::Direction::Left)
        player.setDx (-playerMovementSpeed);
}

PhysicalObject::Position Model::canMove (PhysicalObject *obj, PhysicalObject::Position position)
{
    PhysicalObject::Position ret (position);
    for (std::vector<PhysicalObject>::const_iterator i = nonActiveObjs.cbegin (); i != nonActiveObjs.cend (); i++)
    {
        if (&(*i) != obj)
        {
            PhysicalObject::Position pos = collides (*obj, *i, position);
            if (abs (pos.x - obj->getX ()) < abs (ret.x - obj->getX ()))
                ret.x = pos.x;
            if (abs (pos.y - obj->getY ()) < abs (ret.y - obj->getY ()))
                ret.y = pos.y;
        }
    }
    return ret;
}

PhysicalObject::Position
Model::collides (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos)
{
    int y11 = obj1.getY ();
    int y12 = y11 + obj1.getSizey ();
    int y21 = obj2.getY ();
    int y22 = y21 + obj2.getSizey ();
    int x11 = obj1.getX ();
    int x12;
    int x21 = obj2.getX ();
    int x22 = x21 + obj2.getSizex ();
    if (y11 >= y21 && y11 <= y22 || y21 >= y11 && y21 <= y12)
    {
        if (pos.x > x11)
        {
            if (x21 >= x11 && x21 - obj1.getSizex () <= pos.x)
                pos.x = x21 - obj1.getSizex () - 1;
        } else
        {
            if (x21 <= x11 && x22 >= pos.x)
                pos.x = x22 + 1;
        }
    }
    x11 = pos.x;
    x12 = x11 + obj1.getSizex ();
    if (x11 >= x21 && x11 <= x22 || x21 >= x11 && x21 <= x12)
    {
        if (pos.y > y11)
        {
            if (y21 >= y11 && y21 - obj1.getSizey () <= pos.y)
                pos.y = y21 - obj1.getSizey () - 1;
        } else
        {
            if (y21 <= y11 && y22 >= pos.y)
                pos.y = y22 + 1;
        }
    }
    return pos;
}




