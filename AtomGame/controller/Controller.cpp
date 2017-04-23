//
// Created by sl on 18.04.17.
//

#include "Controller.h"

log4cpp::Category& Controller::logger = log4cpp::Category::getInstance(typeid(Controller).name());

void Controller::onRightKeyPress() {
    model->movePlayer(Actor::Direction::Right);
}

void Controller::onLeftKeyPress() {
    model->movePlayer(Actor::Direction::Left);
}

void Controller::onUpKeyPress() {
    model->movePlayer(Actor::Direction::Up);
}

void Controller::onDownKeyPress() {
    model->movePlayer(Actor::Direction::Down);
}

void Controller::SetView(View* view) {
    this->view = view;
}

Controller::Controller(Model *model): model(model), view(nullptr) {
    logger.info("Controller init");
}
