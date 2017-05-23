//
// Created by sl on 18.04.17.
//

#include "Controller.h"

log4cpp::Category &Controller::logger = log4cpp::Category::getInstance (typeid (Controller).name ());

void Controller::onRightKeyPress ()
{
    model->movePlayer (Actor::Direction::Right);
}

void Controller::onLeftKeyPress ()
{
    model->movePlayer (Actor::Direction::Left);
}

void Controller::onUpKeyPress ()
{
    model->movePlayer (Actor::Direction::Up);
}

void Controller::onDownKeyPress ()
{
    model->movePlayer (Actor::Direction::Down);
}

void Controller::onNoMovementKeyPress ()
{
    model->movePlayer (PhysicalObject::Direction::NoDirection);
}


Controller::Controller (Model *model, View *view) : model (model), view (view)
{
    logger.info ("Controller init");
}

void Controller::tick ()
{
//all presses we need
    bool movementKeyPressed = false;
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right))
    {
        onRightKeyPress ();
        movementKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left))
    {
        onLeftKeyPress ();
        movementKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up))
        onUpKeyPress ();
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down))
        onDownKeyPress ();
    if (!movementKeyPressed)
        onNoMovementKeyPress ();
}

bool Controller::isPressed (sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed (key);
}
