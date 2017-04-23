//
// Created by sl on 06.04.17.
//

#include <memory>

#include "Model.h"

log4cpp::Category& Model::logger = log4cpp::Category::getInstance(typeid(Model).name());

void Model::tick(){
    logger.info("Model tick");
}

void Model::startGame() {

}

void Model::movePlayer(Actor::Direction direction) {
    if (direction==Actor::Direction::Right) player.Move(1,0);//todo add dependency on speed or smth more interesting
    if (direction==Actor::Direction::Left) player.Move(-1,0);
    if (direction==Actor::Direction::Up) player.Move(0,1);
    if (direction==Actor::Direction::Down) player.Move(0,-1);
}

bool Model::isPlayerWin() {
    return false;
}

Model::Model() : player(0, 0), bots(), nonActiveObjs(), gameField(100, 100) {
    logger.info("Model init");

}

const Player &Model::getPlayer() const {
    return player;
}

const std::vector<Bot> &Model::getBots() const {
    return bots;
}

const GameField &Model::getGameField() const {
    return gameField;
}

const std::vector<GameObject> &Model::getNonActiveObjs() const {
    return nonActiveObjs;
}




