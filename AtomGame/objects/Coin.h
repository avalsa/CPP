//
// Created by sl on 13.06.17.
//

#ifndef ATOMGAME_COIN_H
#define ATOMGAME_COIN_H


#include "PhysicalObject.h"

class Coin : public PhysicalObject
{
public:
    Coin(int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block);

    PhysicalObject::BlockType getClass() const;

    bool isPicked() const;
protected:
    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

private:
    bool _isPicked;
    void load(tinyxml2::XMLElement *pElement);
};


#endif //ATOMGAME_COIN_H
