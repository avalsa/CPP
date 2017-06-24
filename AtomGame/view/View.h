//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_VISUALIZER_H
#define ATOMGAME_VISUALIZER_H

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

    void onCoinPick();

    void onDieBot(Actor* bot);

    void onShot();

    struct AnimInfo
    {
        Actor* _obj;
        Animation* _anim;
        int _left;

        AnimInfo( Animation *anim, Actor* obj);
    };

private:

    void showPlayerStat();

    void showGameOver (bool isRespawnable, bool isShow);

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
    std::vector<struct AnimInfo> _tempAnim;
    std::map<PhysicalObject*, Animation*> block_animations;

    void drawObject(sf::Sprite* sprite, PhysicalObject* object, bool slaceX, bool scaleY);

    sf::Sprite getActionSprite(const Actor *pActor, Animation *&pAnimation);
};

#endif //ATOMGAME_VISUALIZER_H
