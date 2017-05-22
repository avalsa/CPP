//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_PLAYER_H
#define ATOMGAME_PLAYER_H


#include "Actor.h"

class Player : public Actor
{
public:
    Player (int x, int y, int sizeX, int sizeY);

    void respawn ();

private:
    int _respX;
    int _respY;

protected:
    virtual void collided (const PhysicalObject &source, Axis relativeLocation);

};


#endif //ATOMGAME_PLAYER_H
