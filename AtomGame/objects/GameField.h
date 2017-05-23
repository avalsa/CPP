//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_GAMEFIELD_H
#define ATOMGAME_GAMEFIELD_H

#include "GameObject.h"

class GameField : public GameObject
{
public:

    GameField (int width, int height);

    int getWidth () const;

    int getHeight () const;

    char getCell (int x, int y);

private:
    int width_;
    int height_;
    char **field_; //todo make not char but enum for ex grass, sky, etc or make class cell with same idea
};


#endif //ATOMGAME_GAMEFIELD_H
