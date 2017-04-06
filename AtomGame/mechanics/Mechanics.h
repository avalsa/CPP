//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_MECHANICS_H
#define ATOMGAME_MECHANICS_H


class Mechanics {
public:
    Mechanics()
    {
        //init objects and graphics
    }

    void NewGame()
    {
        //start new game
        while(true)
            tick();
    }

private:
    void tick()
    {
        //do work of mechanics
        //draw results
        //delay
    }
};


#endif //ATOMGAME_MECHANICS_H
