//
// Created by sl on 27.04.17.
//

#include "AnimationFactory.h"

log4cpp::Category &AnimationFactory::logger = log4cpp::Category::getInstance (typeid (AnimationFactory).name ());

Animation AnimationFactory::playerAnimation = Animation("player.png", load("player.xml"), frameRate * 1.5);

Animation AnimationFactory::teleportAnimation = Animation("teleport.png", load("teleport.xml"), frameRate*4);

AnimationFactory::AnimationFactory ()
{

}

Animation *AnimationFactory::getPlayerAnimation ()
{
    return &playerAnimation;
}

Animation *AnimationFactory::getTeleportAnimation() {
    return &teleportAnimation;
}

std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>>
AnimationFactory::load(const char *file)
{
    char prefix[80] = "view/res/";
    if (file == nullptr)
    {
        logger.warn ("Trying to load animation from nullptr");
        return nullptr;
    }
    logger.info ("Loading animation from \"%s\"", file);
    tinyxml2::XMLDocument fs;
    if (int err = fs.LoadFile (strcat(prefix, file)))
    {
        logger.warn ("Failed to animation from \"%s\", errorID = %d", file, err);
    }
    else {
        logger.info("\"%s\" parsed", file);
        return load(fs, file);
    }

}

std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>>
AnimationFactory::load(tinyxml2::XMLDocument& xmlDocument, const char* file)
{
    std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>> ret(new std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>);

    if(tinyxml2::XMLElement* actions = xmlDocument.FirstChildElement ("Actions"))
    {
        for(tinyxml2::XMLElement* action = actions->FirstChildElement ("Action"); action != nullptr; action = action->NextSiblingElement ("Action") ) {
            const char* typestr = action->Attribute("Type");
            if (typestr != nullptr){
                std::shared_ptr<Animation::FrameSequence> frameSequence(new Animation::FrameSequence(action));
                if (frameSequence->_FrameCount == -1 ||
                        frameSequence->_size_x == -1 || frameSequence->_size_y == -1 ||
                        frameSequence->_init_x == -1 || frameSequence->_init_y == -1 )
                    logger.warn("Problem while loading action of type \"%s\" in file \"%s\"", typestr, file);
                else {
                    int res;
                    std::shared_ptr<Animation::AnimationType> type(new Animation::AnimationType(Animation::makeAnimationType(typestr, res)));
                    if (res) {
                        logger.warn("Problem with type value in \"%s\"", file);
                        continue;
                    }
                    ret->insert(std::pair<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>>(type, frameSequence));
                }
            }
            else
                logger.warn("Type of action is not defined in \"%s\"", file);
        }
        return ret;
    }
    else
        logger.warn ("Animation file \"%s\" has no animations", file);
}


