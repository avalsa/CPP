//
// Created by sl on 06.04.17.
//

#include "Bot.h"

Bot::Bot (int x, int y, int sizeX, int sizeY, int stepCnt) :
        CustomObject (x, y, sizeX, sizeY), _stepCount(stepCnt),
        Actor(x, y, sizeX, sizeY),
        PhysicalObject(x, y, sizeX, sizeY, PhysicalObject::BlockType::Bot)
{}

Bot::Bot(int x, int y, int sizeX, int sizeY, int stepCnt, tinyxml2::XMLElement *pElement) :
        CustomObject(x, y, sizeX, sizeY), _stepCount(stepCnt),
        Actor(x, y, sizeX, sizeY),
        PhysicalObject(x, y, sizeX, sizeY, PhysicalObject::BlockType::Bot)
{
    load(pElement);
    _ay = 1;
}

PhysicalObject::BlockType Bot::getClass() const {
    return PhysicalObject::BlockType::Bot;
}

void Bot::collided(const PhysicalObject *source, PhysicalObject::Axis relativeLocation)
{
    Actor::collided(source, relativeLocation);
}

PhysicalObject::Position Bot::tick()
{
    if (!_alive)
    {
        _vx = _vy = 0;
    }
    if (_alive && proc)
    {
        proc->setReg (_x, 0);
        proc->setReg (_y, 1);
        proc->setReg (_vx, 2);
        proc->setReg (_vy, 3);
        proc->setReg (_ax, 4);
        proc->setReg (_ay, 5);
        proc->setReg(_stepCount, 6);
        proc->setReg(_plPos.x, 8);
        proc->execute ();
        proc->reset ();
        _x = proc->getReg (0);
        _y = proc->getReg (1);
        _vx = proc->getReg (2);
        _vy = proc->getReg (3);
        _ax = proc->getReg (4);
        _ay = proc->getReg (5);
        _lookDirection = _vx > 0 ? Actor::Direction::Right : _vx < 0 ? Actor::Direction::Left : _lookDirection;
        _moving = _vx != 0 ? true : false;
    }
    return PhysicalObject::tick ();
}

void Bot::load(tinyxml2::XMLElement *block) {
    CustomObject::load(block);
    if (tinyxml2::XMLElement *info = block->FirstChildElement ("Step"))
    {
        if (info->Attribute ("Count"))
            _stepCount = info->IntAttribute ("Count");
    }
    if (tinyxml2::XMLElement *info = block->FirstChildElement ("Speed"))
    {
        if (info->Attribute ("X"))
            _vx = info->IntAttribute ("X");
        if (info->Attribute ("Y"))
            _vy = info->IntAttribute ("Y");
    }
}

void Bot::setPlayerPosition(PhysicalObject::Position position)
{
    _plPos = position;
}
