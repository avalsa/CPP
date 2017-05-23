//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_VISUALIZER_H
#define ATOMGAME_VISUALIZER_H

#include "../objects/GameObject.h"
#include "../model/Model.h"
#include "../controller/Controller.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class Controller;

class View
{
public:

    View (Model *, int height, int width);

    int tick ();

    void ShowGameOver ();

    void PlayerWin ();


private:
    static log4cpp::Category &logger;
    Model *model;
    Controller *controller;
    sf::RenderWindow window;
    int offsetX;
    int offsetY;

    Animation *_playerAnimation;
};


#endif //ATOMGAME_VISUALIZER_H
