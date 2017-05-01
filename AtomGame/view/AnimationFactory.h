//
// Created by sl on 27.04.17.
//

#ifndef ATOMGAME_ANIMATIONFATORY_H
#define ATOMGAME_ANIMATIONFATORY_H

#include "Animation.h"
#include "../objects/Player.h"

class AnimationFactory {
public:

    static Animation* getPlayerAnimation();


private:
    static constexpr float frameRate = 0.05f;
    AnimationFactory();
};


#endif //ATOMGAME_ANIMATIONFATORY_H