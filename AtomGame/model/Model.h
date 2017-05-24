//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_MECHANICS_H
#define ATOMGAME_MECHANICS_H


#include <log4cpp/Category.hh>
#include <typeinfo>
#include <queue>
#include "../objects/Player.h"
//#include "../objects/Bot.h"
#include "../objects/GameField.h"
#include "../objects/TransMapTeleporter.h"

class Model
{
public:
    Model ();        //init controller

    ~Model ();

    void tick (); //do work of model

    bool isPlayerWin ();

    bool isGameOver ();

    void startGame ();

    void movePlayer (Actor::Direction direction);

    void actPlayer (Actor::Action action);

    //const std::vector<Bot> &getBots () const;

    const GameField &getGameField () const;

    std::vector<PhysicalObject *> &getObjs ();

    Player &getPlayer ();

    void load(const char* xmlfile, const char* name = nullptr);

    void load(tinyxml2::XMLDocument& xmlDocument, const char* name = nullptr);

    void load(tinyxml2::XMLElement* map);

private:
    static log4cpp::Category &logger;
    Player player;
    //std::vector<Bot> bots;
    std::vector<PhysicalObject *> objs; //for movement algorithm standardization
    GameField gameField;
    TransMapTeleporter *teleporter;

    void tryMove (PhysicalObject &obj, PhysicalObject::Position position);

    static std::pair<bool, int>
    collidesOnX (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos);

    static std::pair<bool, int>
    collidesOnY (const PhysicalObject &obj1, const PhysicalObject &obj2, PhysicalObject::Position pos);

    const int gravity = 1;
    const int jumpStrength = 20;
    const int playerMovementSpeed = 5;

};

#endif //ATOMGAME_MECHANICS_H
