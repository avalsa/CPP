//
// Created by sl on 18.04.17.
//

#ifndef ATOMGAME_ATOMGAME_H
#define ATOMGAME_ATOMGAME_H

#include "../model/Model.h"
#include "../view/View.h"

class View;

class Controller
{
public:

    Controller (Model *, View *);

    void onRightKeyPress ();

    void onLeftKeyPress ();

    void onUpKeyPress ();

    void onDownKeyPress ();

    void onNoMovementKeyPress ();

    void tick ();

private:
    static log4cpp::Category &logger;
    Model *model;
    View *view;
};

#endif //ATOMGAME_ATOMGAME_H
