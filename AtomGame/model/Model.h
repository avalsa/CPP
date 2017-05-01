//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_MECHANICS_H
#define ATOMGAME_MECHANICS_H


#include <log4cpp/Category.hh>
#include <typeinfo>
#include <queue>
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

    void actPlayer (Actor::Action action);

    const std::vector<Bot> &getBots() const;

    const GameField &getGameField() const;

    const std::vector<PhysicalObject> &getNonActiveObjs () const;

    const Player &getPlayer() const;

private:
    static log4cpp::Category& logger;
    Player player;
    std::vector<Bot> bots;
    std::vector<PhysicalObject> nonActiveObjs;
    GameField gameField;

    PhysicalObject::Position canMove (PhysicalObject *obj, PhysicalObject::Position position);

    static PhysicalObject::Position
    collides (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos);

    const int playerMovementSpeed = 5;

};

#endif //ATOMGAME_MECHANICS_H
