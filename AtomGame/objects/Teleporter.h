//
// Created by svuatoslav on 5/22/17.
//

#ifndef ATOMGAME_TELEPORTER_H
#define ATOMGAME_TELEPORTER_H


#include "CustomObject.h"

class Teleporter : public CustomObject
{
private:
    int _destX;
    int _destY;

protected:
    void load (tinyxml2::XMLElement *block);
public:
    Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY);

    Teleporter (int x, int y, int sizeX, int sizeY, const char *file);

    Teleporter (int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block);

    int getDestX ();

    int getDestY ();

    virtual BlockType getClass () const;

protected:
    Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, BlockType type);
};


#endif //ATOMGAME_TELEPORTER_H
