//
// Created by sl on 18.04.17.
//

#include "Controller.h"

log4cpp::Category &Controller::logger = log4cpp::Category::getInstance (typeid (Controller).name ());

void Controller::onRightKeyPress (float stregth)
{
    model->movePlayer (Actor::Direction::Right,stregth);
}

void Controller::onLeftKeyPress (float stregth)
{
    model->movePlayer (Actor::Direction::Left,stregth);
}

void Controller::onUpKeyPress ()
{
    model->movePlayer (Actor::Direction::Up,0);
}

void Controller::onDownKeyPress (float stregth)
{
    model->movePlayer (Actor::Direction::Down,stregth);
}

void Controller::onNoMovementKeyPress ()
{
    model->movePlayer (PhysicalObject::Direction::NoDirection,0);
}

void Controller::onSpacePress()
{
    model->shootPlayer();
}

Controller::Controller (Model *model, View *view) : model (model), view (view)
{
    logger.info ("Controller init");
}

void Controller::tick ()
{
    if(sf::Joystick::isConnected (0))
    {
        float axisRushPosition = sf::Joystick::getAxisPosition (0,sf::Joystick::Axis::R);
        std::cout<<axisRushPosition<<'\n';
        float axisXPosition = sf::Joystick::getAxisPosition (0,sf::Joystick::Axis::X);
        if(axisXPosition<-10)
            onLeftKeyPress (-axisXPosition*(axisRushPosition+500)/400);
        else
        if(axisXPosition>10)
            onRightKeyPress (axisXPosition*(axisRushPosition+500)/400);
        else
            onNoMovementKeyPress ();
        if(float axisYPosition = sf::Joystick::getAxisPosition (0,sf::Joystick::Axis::Y) > 0)
            onDownKeyPress (axisYPosition);
        if(sf::Joystick::isButtonPressed (0,0))
            onUpKeyPress ();
        if(sf::Joystick::isButtonPressed (0,1) && axisRushPosition == -100)
            onSpacePress ();
    }
    else
    {
        //all presses we need
        bool movementKeyPressed = false;
        bool rush = sf::Keyboard::isKeyPressed (sf::Keyboard::LShift);
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Right))
        {
            onRightKeyPress (100 + (rush? 50 : 0));
            movementKeyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Left))
        {
            onLeftKeyPress (100 + (rush? 50 : 0));
            movementKeyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Up))
            onUpKeyPress ();
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Down))
            onDownKeyPress (100);
        if (!movementKeyPressed)
            onNoMovementKeyPress ();
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Space) && !rush)
            onSpacePress ();
    }
}

bool Controller::isPressed (sf::Keyboard::Key key)
{
    return sf::Keyboard::isKeyPressed (key);
}

bool Controller::isEnd ()
{
    return sf::Keyboard::isKeyPressed (sf::Keyboard::Key::Escape);
}

void Controller::onMapChange(const char* mapName) {
    view->changeMap(mapName);
}

void Controller::onCoinPicked() {
    view->onCoinPick();
}

void Controller::onDieBot(Actor* obj)
{
    view->onDieBot(obj);
}

void Controller::onShot()
{
    view->onShot();
}
