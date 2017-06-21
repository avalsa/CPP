//
// Created by sl on 27.04.17.
//

#include <cstring>
//#include <log4cpp/Category.hh>
#include "Animation.h"

log4cpp::Category &Animation::logger = log4cpp::Category::getInstance (typeid (Animation).name ());

sf::Sprite Animation::getNextSprite (PhysicalObject::Direction direction)
{
    _currentFrame += _frameRate;
    std::shared_ptr<Animation::AnimationType> key(new AnimationType(_animationType));
    std::shared_ptr<FrameSequence> frameSequence = (*_animations)[key];
    if (frameSequence->_FrameCount < _currentFrame) _currentFrame = .0f;
    static bool isInv;
    if (direction == PhysicalObject::Direction::Right) isInv = 0;
    if (direction == PhysicalObject::Direction::Left) isInv = 1;
    //but if No we have previous dir
    if (isInv)
    {
        _sprite.setTextureRect (sf::IntRect (
                frameSequence->_init_x + frameSequence->_size_x + frameSequence->_size_x * (int) _currentFrame,
                frameSequence->_init_y,
                -frameSequence->_size_x,
                frameSequence->_size_y));
    } else
    {
        _sprite.setTextureRect (sf::IntRect (
                frameSequence->_init_x + frameSequence->_size_x * (int) _currentFrame,
                frameSequence->_init_y,
                frameSequence->_size_x,
                frameSequence->_size_y));
    }
    return _sprite;
}

void Animation::setAnimationType (Animation::AnimationType type)
{
    _animationType = type;
    _currentFrame = .0f;
}

Animation::AnimationType Animation::getAnimationType () const
{
    return _animationType;
}

Animation::Animation (const char *fileName, std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType>, std::shared_ptr<Animation::FrameSequence>, Animation::Comp>> frames, float frameRate) :
        _currentFrame (.0f), _frameRate (frameRate),
        _sprite (), _texture (), _animations(frames) {
    logger.info("Loading texture from file \"%s\"", fileName);
    char prefix[80] = "view/res/";
    if (!_texture.loadFromFile(strcat(prefix, fileName)))
        logger.warn("Problem in loading \"%s\"", fileName);
    else
        _sprite.setTexture(_texture);
}

Animation::AnimationType Animation::makeAnimationType(const char *string, int& retcode) {
    retcode = 0;
    if (!strcmp(string, "None"))
        return AnimationType::None;
    if (!strcmp(string, "Move"))
        return AnimationType::Move;
    if (!strcmp(string, "Jump"))
        return AnimationType::Jump;
    if (!strcmp(string, "Stand"))
        return AnimationType::Stand;
    if (!strcmp(string, "Die"))
        return AnimationType::Die;
    logger.warn("No animation Type associated with \"%s\" found", string);
    retcode = 1;
    return  AnimationType::None;
}

int Animation::getCountFrames() {
    std::shared_ptr<Animation::AnimationType> key(new AnimationType(_animationType));
    std::shared_ptr<FrameSequence> frameSequence = (*_animations)[key];
    return frameSequence->_FrameCount;
}

float Animation::getFrameRate() {
    return _frameRate;
}

Animation::FrameSequence::FrameSequence (int frameCount, int init_x, int init_y, int size_x, int size_y) :
        _FrameCount (frameCount),
        _init_x (init_x), _init_y (init_y),
        _size_x (size_x), _size_y (size_y) {}

Animation::FrameSequence::FrameSequence(tinyxml2::XMLElement *action) :
        _FrameCount (-1), _init_x (-1), _init_y (-1), _size_x (-1), _size_y (-1)
{
    if (tinyxml2::XMLElement* place = action->FirstChildElement("Place"))
    {
        if (place->Attribute("X"))
            this->_init_x = place->IntAttribute("X");
        else
            logger.warn("No init X attribute");
        if (place->Attribute("Y"))
            this->_init_y = place->IntAttribute("Y");
        else
            logger.warn("No init Y attribute");
    } else
        logger.warn("No place information");

    if (tinyxml2::XMLElement* size = action->FirstChildElement("Size"))
    {
        if (size->Attribute("X"))
            this->_size_x = size->IntAttribute("X");
        else
            logger.warn("No size X attribute");
        if (size->Attribute("Y"))
            this->_size_y = size->IntAttribute("Y");
        else
            logger.warn("No size Y attribute");
    } else
        logger.warn("No size information");

    if (tinyxml2::XMLElement* frames = action->FirstChildElement("Frames"))
    {
        if (frames->Attribute("Count"))
            this->_FrameCount = frames->IntAttribute("Count");
        else
            logger.warn("No frames Count attribute");
    } else
        logger.warn("No frames information");
}

bool Animation::Comp::operator()(const std::shared_ptr<Animation::AnimationType> a,
                                  const std::shared_ptr<Animation::AnimationType> b) const
{
    return (*a)<(*b);
}