//
// Created by sl on 27.04.17.
//

#include "AnimationFactory.h"

AnimationFactory::AnimationFactory ()
{

}

Animation *AnimationFactory::getPlayerAnimation ()
{
    //todo find a better solution
    static Animation playerAnimation ("player.png", frameRate);
    return &playerAnimation;
    //return new Animation("player.png", frameRate);  //fixme im eating your ram
}
