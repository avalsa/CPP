//
// Created by sl on 27.04.17.
//

#ifndef ATOMGAME_ANIMATIONFATORY_H
#define ATOMGAME_ANIMATIONFATORY_H

#include "Animation.h"
#include "../objects/Player.h"
#include <tinyxml2.h>
#include <memory>

class AnimationFactory
{
public:

    static Animation *getPlayerAnimation ();

    static Animation *getTeleportAnimation();

    static Animation *getMapChangeAnimation();

    static Animation *getRespawnAnimation();

    static Animation *getCoinAnimation();


private:

    static Animation playerAnimation;

    static Animation teleportAnimation;

    static Animation mapchangeAnimation;

    static Animation respawnAnimation;

    static Animation coinAnimation;

    static log4cpp::Category &logger;

    static constexpr float frameRate = 0.05f;

    AnimationFactory ();

    static
    std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>>
    load(const char *file);

    static
    std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>>
    load(tinyxml2::XMLDocument& xmlDocument, const char *file);
};

#endif //ATOMGAME_ANIMATIONFATORY_H