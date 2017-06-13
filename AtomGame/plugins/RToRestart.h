//
// Created by svuatoslav on 5/23/17.
//

#ifndef ATOMGAME_RTORESTART_H
#define ATOMGAME_RTORESTART_H

#include "plugin/Plugin.h"

class RToRestart : public Plugin
{
private:
    Model *_model;
    Controller *_controller;
public:
    RToRestart ();

    virtual void start (Model *model, Controller *controller, View *view);

    virtual void tick ();
};

#endif //ATOMGAME_RTORESTART_H
