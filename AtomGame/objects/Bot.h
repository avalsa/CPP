//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_BOT_H
#define ATOMGAME_BOT_H

#include "CustomObject.h"
#include "Actor.h"

class Bot : public CustomObject, public Actor
{
public:

    Bot (int x, int y, int sizeX, int sizeY, int stepCount);

    Bot(int, int, int, int,int, tinyxml2::XMLElement *pElement);

    PhysicalObject::BlockType getClass() const;

    Position tick();

protected:

    void load (tinyxml2::XMLElement *block);

    virtual void collided (const PhysicalObject *source, Axis relativeLocation);

private:
    int _stepCount;
};


#endif //ATOMGAME_BOT_H
