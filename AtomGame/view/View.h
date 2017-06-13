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
#include <memory>

class Controller;

class Model;

class View
{
public:

    enum BackgroundType
    { City1, City2};

    View (Model *, int height, int width);

    int tick ();

    void changeMap(const char *string);

private:

    void showGameOver ();

    void showPlayerWin ();

    void clear();

    bool isVisible(const PhysicalObject* obj) const;

    static log4cpp::Category &logger;
    Model *model;
    Controller *controller;
    sf::RenderWindow window;
    int offsetX;
    int offsetY;
    Animation *_playerAnimation;
    BackgroundType backgroundType;

    void drawObject(sf::Sprite* sprite, PhysicalObject* object, bool slaceX, bool scaleY);



};


#endif //ATOMGAME_VISUALIZER_H
