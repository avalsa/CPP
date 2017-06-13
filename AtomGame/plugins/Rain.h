//
// Created by svuatoslav on 5/23/17.
//

#ifndef ATOMGAME_RAIN_H
#define ATOMGAME_RAIN_H


#include "plugin/Plugin.h"

class Rain : public Plugin
{
private:
    const int period = 10;
    const int diameter = 1000;
    const int height = 1000;
    const int size = 5;
    int timer;
    Model *_model;
    std::vector<PhysicalObject *> drops;
public:


    virtual void start (Model *model, Controller *controller, View *view);

    virtual void tick ();
};


#endif //ATOMGAME_RAIN_H
