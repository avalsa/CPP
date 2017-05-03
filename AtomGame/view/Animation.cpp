//
// Created by sl on 27.04.17.
//

#include <cstring>
//#include <log4cpp/Category.hh>
#include "Animation.h"
#include <memory>

log4cpp::Category &Animation::logger = log4cpp::Category::getInstance (typeid (Animation).name ());
std::map<const char *, int> Animation::files = {
        {"player.png", Files::PLAYER},
        {"bot.gif",    Files::BOT}};

const sf::Sprite Animation::getNextSprite (PhysicalObject::Direction direction)
{
    _currentFrame += _frameRate;
    FrameSequence *frameSequence = _animations[_animationType];
    if (frameSequence->_FrameCount < _currentFrame) _currentFrame = .0f;
    //log(_currentFrame);
    logger.warn (std::to_string (_currentFrame));
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

Animation::Animation (const char *fileName, float frameRate) :
        _currentFrame (.0f), _frameRate (frameRate),
        _sprite (), _texture ()
{
    logger.info (fileName);
    char prefix[80] = "view/res/";
    _texture.loadFromFile (strcat (prefix, fileName));
    _sprite.setTexture (_texture);

    switch (files[fileName])
    {
        case Files::PLAYER:
        {
            //coords can be easily removed to file...
            //or even make provider which will know all this stuff
            //for move
            FrameSequence *move = new FrameSequence (4, 0, 80, 38, 42);
            //for jump
            FrameSequence *jump = new FrameSequence (4, 0, 48, 29, 26);
            //for stand
            FrameSequence *stand = new FrameSequence (2, 0, 1, 37, 42);

            _animations.insert (std::pair<AnimationType, FrameSequence *> (AnimationType::Move, move));
            _animations.insert (std::pair<AnimationType, FrameSequence *> (AnimationType::Jump, jump));
            _animations.insert (std::pair<AnimationType, FrameSequence *> (AnimationType::Stand, stand));
        }
            break;
        default:
            throw std::out_of_range ("We already know about problem. Fix soon!");
    }
}

Animation::~Animation ()
{
    for (auto e:_animations)
    {
        delete e.second;
    }
}

Animation::FrameSequence::FrameSequence (int frameCount, int init_x, int init_y, int size_x, int size_y) :
        _FrameCount (frameCount),
        _init_x (init_x), _init_y (init_y),
        _size_x (size_x), _size_y (size_y) {}
