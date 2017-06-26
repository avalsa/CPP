//
// Created by sl on 13.06.17.
//

#include "Coin.h"

Coin::Coin(int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block) :
        PhysicalObject(x, y, sizeX, sizeY, PhysicalObject::BlockType::Coin), _isPicked(false)
{
    load(block);
}

PhysicalObject::BlockType Coin::getClass() const
{
    return PhysicalObject::BlockType::Coin;
}

void Coin::load(tinyxml2::XMLElement *block)
{
    if (tinyxml2::XMLElement *coordinates = block->FirstChildElement ("Place"))
    {
        if (coordinates->Attribute ("X"))
            _x = coordinates->IntAttribute ("X");
        if (coordinates->Attribute ("Y"))
            _y = coordinates->IntAttribute ("Y");
    }
    if (tinyxml2::XMLElement *size = block->FirstChildElement ("Size"))
    {
        if (size->Attribute ("X"))
            _sizeX = size->IntAttribute ("X");
        if (size->Attribute ("Y"))
            _sizeY = size->IntAttribute ("Y");
    }
}

void Coin::collided(const PhysicalObject *source, PhysicalObject::Axis relativeLocation) {
    if (source->type () == PhysicalObject::BlockType::Player)
        _isPicked = true;
}

bool Coin::isPicked() const {
    return _isPicked;
}
