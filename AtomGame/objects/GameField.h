//
// Created by sl on 06.04.17.
//

#ifndef ATOMGAME_GAMEFIELD_H
#define ATOMGAME_GAMEFIELD_H

#include <vector>
#include "GameObject.h"
#include "Player.h"

class GameField {
public:
    GameField(std::vector<GameObject>& objects, Player *player) : objs_(&objects), player_(player)
    {}

    void PerformGameLogic(){
        // proccess all attacks, moves and so on
    }

private:
    std::vector<GameObject> *objs_;
    Player *player_;
};


#endif //ATOMGAME_GAMEFIELD_H
