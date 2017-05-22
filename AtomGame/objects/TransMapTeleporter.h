//
// Created by svuatoslav on 5/22/17.
//

#ifndef ATOMGAME_TRANSMAPTELEPORTER_H
#define ATOMGAME_TRANSMAPTELEPORTER_H


#include "Teleporter.h"

class TransMapTeleporter : public Teleporter
{
public:
    TransMapTeleporter (int x, int y, int sizeX, int sizeY, int destX, int destY, const char *destMap,
                        const char *file = nullptr);

    virtual ~TransMapTeleporter ();

    const char *getDest ();

private:
    char *_destination;

    virtual BlockType getClass () const;
};


#endif //ATOMGAME_TRANSMAPTELEPORTER_H
