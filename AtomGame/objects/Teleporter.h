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
public:
    Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *file = nullptr);

    int getDestX ();

    int getDestY ();

    virtual BlockType getClass () const;

protected:
    Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, BlockType type, const char *file = nullptr);
};


#endif //ATOMGAME_TELEPORTER_H
