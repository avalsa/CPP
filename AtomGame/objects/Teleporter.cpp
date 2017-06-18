//
// Created by svuatoslav on 5/22/17.
//

#include "Teleporter.h"

PhysicalObject::BlockType Teleporter::getClass () const
{
    return PhysicalObject::BlockType::Portal;
}

int Teleporter::getDestX ()
{
    return _destX;
}

int Teleporter::getDestY ()
{
    return _destY;
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, const char *file) :
        CustomObject (x, y, sizeX, sizeY),
        PhysicalObject(x, y, sizeX, sizeY, BlockType::Portal)
{
    if (file == nullptr)
        return;
    tinyxml2::XMLDocument settings;
    if (int err = settings.LoadFile (file))
    {
        logger.warn ("Failed to load settings from \"%s\", errorID = %d", file, err);
    } else
    {
        logger.info ("\"%s\" parsed", file);
    }
    if (tinyxml2::XMLElement *block = settings.FirstChildElement ("Block"))
    {
        load (block);
        CustomObject::load (block);
    }
}

void Teleporter::load (tinyxml2::XMLElement *block)
{
    if (tinyxml2::XMLElement *dest = block->FirstChildElement ("Portal"))
    {
        if (dest->Attribute ("X"))
        {
            _destX = dest->IntAttribute ("X");
        } else
        {
            logger.warn ("Portal destination X is not specified");
            _destX = 0;
        }
        if (dest->Attribute ("Y"))
        {
            _destY = dest->IntAttribute ("Y");
        } else
        {
            logger.warn ("Portal destination Y is not specified");
            _destY = 0;
        }
    } else
    {
        logger.warn ("Portal destination not specified, creating solid block instead");
        _destX = 0;
        _destY = 0;
        block->SetAttribute ("Type", "Solid");
    }
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY) :
        CustomObject (x, y, sizeX, sizeY, Portal),
        PhysicalObject(x, y, sizeX, sizeY, Portal),
        _destX (destX), _destY (destY)

{
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block) :
        CustomObject (x, y, sizeX, sizeY, block),
        PhysicalObject(x, y, sizeX, sizeY, BlockType::Portal)
{
    if (block != nullptr)
    {
        load (block);
        CustomObject::load (block);
    } else
        logger.warn ("Missing XML element for portal, created solid block instead");
}

Teleporter::Teleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, PhysicalObject::BlockType type)
        : CustomObject (x, y, sizeX, sizeY, type),
          PhysicalObject(x, y, sizeX, sizeY, BlockType::Portal),
          _destX (destX), _destY (destY)
{
}
