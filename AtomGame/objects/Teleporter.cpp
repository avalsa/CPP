//
// Created by svuatoslav on 5/22/17.
//

#include "Teleporter.h"

PhysicalObject::BlockType Teleporter::getClass () const
{
    return PhysicalObject::BlockType::Portal;
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *file) : CustomObject (x,
                                                                                                                    y,
                                                                                                                    sizeX,
                                                                                                                    sizeY,
                                                                                                                    file,
                                                                                                                    Portal),
                                                                                                      _destX (destX),
                                                                                                      _destY (destY)
{
}

int Teleporter::getDestX ()
{
    return _destX;
}

int Teleporter::getDestY ()
{
    return _destY;
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, BlockType type, const char *file) :
        CustomObject (x, y, sizeX, sizeY, file, type), _destX (destX), _destY (destY)
{
}
