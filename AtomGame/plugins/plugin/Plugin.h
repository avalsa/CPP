//
// Created by svuatoslav on 5/23/17.
//

#ifndef ATOMGAME_PLUGIN_H
#define ATOMGAME_PLUGIN_H


#include "../../model/Model.h"
#include "../../controller/Controller.h"

class Plugin
{
public:
    virtual void start (Model *model, Controller *controller, View *view) = 0;

    virtual void tick () = 0;

    virtual ~Plugin ();
};


#endif //ATOMGAME_PLUGIN_H
