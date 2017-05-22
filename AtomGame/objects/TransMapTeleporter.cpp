//
// Created by svuatoslav on 5/22/17.
//

#include "TransMapTeleporter.h"

PhysicalObject::BlockType TransMapTeleporter::getClass () const
{
    return PhysicalObject::BlockType::TransDimensionalPortal;
}

TransMapTeleporter::TransMapTeleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *destMap,
                                        const char *file)
        : Teleporter (x, y, sizeX, sizeY, destX, destY, PhysicalObject::BlockType::TransDimensionalPortal, file),
          _destination (nullptr)
{
    if (!destMap)
        return;
    _destination = strdup (destMap);
}

TransMapTeleporter::~TransMapTeleporter ()
{
    delete _destination;
}

const char *TransMapTeleporter::getDest ()
{
    return _destination;
}
