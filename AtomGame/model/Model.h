//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_MECHANICS_H
#define ATOMGAME_MECHANICS_H


#include <log4cpp/Category.hh>
#include <typeinfo>
#include "../objects/Player.h"
#include "../objects/Bot.h"
#include "../objects/GameField.h"

class Model {
public:
    Model();        //init controller

    void tick(); //do work of model

    bool isPlayerWin();

    bool isGameOver();

    void startGame();

    void movePlayer(Actor::Direction direction);

    const std::vector<Bot> &getBots() const;

    const GameField &getGameField() const;

    const std::vector<GameObject> &getNonActiveObjs() const;

    const Player &getPlayer() const;

private:
    static log4cpp::Category& logger;
    Player player;
    std::vector<Bot> bots;
    std::vector<GameObject> nonActiveObjs;
    GameField gameField;
};


#endif //ATOMGAME_MECHANICS_H
