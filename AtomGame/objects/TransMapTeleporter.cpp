//
// Created by svuatoslav on 5/22/17.
//

#include "TransMapTeleporter.h"

PhysicalObject::BlockType TransMapTeleporter::getClass () const
{
    return PhysicalObject::BlockType::MapChange;
}

TransMapTeleporter::~TransMapTeleporter ()
{
    delete _destinationFile;
}

const char *TransMapTeleporter::getDest ()
{
    return _destination;
}

TransMapTeleporter::TransMapTeleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *destFile,
                                        const char *destMap) :
        Teleporter (x, y, sizeX, sizeY, destX, destY, PhysicalObject::BlockType::MapChange),
        PhysicalObject(x, y, sizeX, sizeY),
        _destinationFile (nullptr)
{
    if (!destFile)
        return;
    _destinationFile = strdup (destFile);
    if (!destMap)
        return;
   strcpy(_destination, destMap);
}

void TransMapTeleporter::load (tinyxml2::XMLElement *block)
{
    if (tinyxml2::XMLElement *map = block->FirstChildElement ("Map"))
    {
        if (const char *file = map->Attribute ("File"))
        {
            _destinationFile = strdup (file);
        } else
        {
            logger.warn ("Map for change is not specified, creating portal instead");
            block->SetAttribute ("Type", "Portal");
            return;
        }
        if (const char *name = map->Attribute ("Name"))
        {
            strcpy(_destination, name);
        }
        return;
    }
    logger.warn ("Map for change is not specified, creating portal instead");
    block->SetAttribute ("Type", "Portal");
}

TransMapTeleporter::TransMapTeleporter (int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block) :
        Teleporter (x, y, sizeX, sizeY, block),
        PhysicalObject(x, y, sizeX, sizeY, BlockType::Portal)
{
    if (block != nullptr)
    {
        load (block);
        Teleporter::load (block);
    } else
        logger.warn ("Missing XML element for MapChanger, created solid block instead");
}

TransMapTeleporter::TransMapTeleporter (int x, int y, int sizeX, int sizeY, const char *file) :
        Teleporter (x, y, sizeX, sizeY, file),
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
        Teleporter::load (block);
    }
}

const char *TransMapTeleporter::getDestFile ()
{
    return &_destinationFile[0];
}
