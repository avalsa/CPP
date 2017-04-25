//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_PLAYER_H
#define ATOMGAME_PLAYER_H


#include "Actor.h"

class Player : public Actor
{
private:
    int _dx;
public:
    void setDx (int _dx);

    void setDy (int _dy);

private:
    int _dy;
public:
    Player (int x, int y, int sizex, int sizey);

    virtual PhysicalObject::Position tick ();
};


#endif //ATOMGAME_PLAYER_H
