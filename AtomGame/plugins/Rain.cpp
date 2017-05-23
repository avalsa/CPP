//
// Created by svuatoslav on 5/23/17.
//

#include "Rain.h"

void Rain::start (Model *model, Controller *controller, View *view)
{
    _model = model;
    timer = 0;
    srand (time (0));
}

void Rain::tick ()
{
    if (timer == period)
    {
        PhysicalObject *drop = new PhysicalObject (rand () % diameter - diameter / 2 + _model->getPlayer ().getX (),
                                                   _model->getPlayer ().getY () - height, size, size);
        drop->setVelocity (0, 1);
        drop->setAcceleration (0, 1);
        drops.push_back (drop);
        _model->getBlocks ().push_back (drop);
        _model->getObjs ().push_back (drop);
        timer = 0;
    } else
        timer++;
    for (std::vector<PhysicalObject *>::const_iterator i = drops.cbegin (); i != drops.cend (); i++)
    {
        if ((*i)->getVy () <= 0)
        {
            for (std::vector<PhysicalObject *>::const_iterator j = _model->getBlocks ().cbegin ();
                 j != _model->getBlocks ().cend (); j++)
            {
                if (*j == *i)
                {
                    _model->getBlocks ().erase (j);
                    break;
                }
            }
            for (std::vector<PhysicalObject *>::const_iterator j = _model->getObjs ().cbegin ();
                 j != _model->getObjs ().cend (); j++)
            {
                if (*j == *i)
                {
                    _model->getObjs ().erase (j);
                    break;
                }
            }
            delete *i;
            i = drops.erase (i);
        }
    }
}

extern "C" Plugin *create ()
{
    return new Rain;
}
