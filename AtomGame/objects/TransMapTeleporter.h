//
// Created by svuatoslav on 5/22/17.
//

#ifndef ATOMGAME_TRANSMAPTELEPORTER_H
#define ATOMGAME_TRANSMAPTELEPORTER_H


#include "Teleporter.h"

class TransMapTeleporter : public Teleporter
{
public:
    TransMapTeleporter (int x, int y, int sizeX, int sizeY, const char *file);

    TransMapTeleporter (int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block);

    TransMapTeleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *destMap);

    virtual ~TransMapTeleporter ();

    const char *getDest ();

private:
    char *_destination;

    virtual BlockType getClass () const;

protected:
    void load (tinyxml2::XMLElement *block);
};


#endif //ATOMGAME_TRANSMAPTELEPORTER_H
