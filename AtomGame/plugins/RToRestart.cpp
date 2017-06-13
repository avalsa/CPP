//
// Created by svuatoslav on 5/23/17.
//

#include "RToRestart.h"

void RToRestart::start (Model *model, Controller *controller, View *view)
{
    _model = model;
    _controller = controller;
}

void RToRestart::tick ()
{
    if (_model && _controller)
        if (_controller->isPressed (sf::Keyboard::Key::R))
            _model->getPlayer ().respawn ();
}

RToRestart::RToRestart () : _model (nullptr), _controller (nullptr)
{
}

extern "C" Plugin *create ()
{
    return new RToRestart;
}
