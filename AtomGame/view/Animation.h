//
// Created by sl on 27.04.17.
//

#ifndef ATOMGAME_ANIMATION_H
#define ATOMGAME_ANIMATION_H

#include <log4cpp/Category.hh>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "../objects/PhysicalObject.h"

class Animation
{
public:

    enum AnimationType
    { //not the same as objects/action
        Move, Jump, Stand, Die, None
    };

    struct FrameSequence
    {
        int _FrameCount;
        int _init_x; //init point for frame offset
        int _init_y;
        int _size_x; //size of one frame
        int _size_y;

        FrameSequence(tinyxml2::XMLElement *action);
        FrameSequence (int frameCount, int init_x, int init_y, int size_x, int size_y);
    };

    struct Comp
    {
        bool operator()(const std::shared_ptr<AnimationType> a, const std::shared_ptr<AnimationType > b) const;
    };

    static AnimationType makeAnimationType(const char* string, int& retcode);

    AnimationType getAnimationType () const;

    void setAnimationType (AnimationType type);

    Animation (const char *, std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType> , std::shared_ptr<Animation::FrameSequence>, Comp>> frames,  float frameRate); //file name, frameRate << 1

    sf::Sprite getNextSprite (PhysicalObject::Direction direction);

private:

    static log4cpp::Category &logger;

    float _frameRate;
    float _currentFrame;
    sf::Texture _texture;
    sf::Sprite _sprite;
    AnimationType _animationType;

    std::shared_ptr<std::map<std::shared_ptr<Animation::AnimationType> , std::shared_ptr<Animation::FrameSequence>, Comp>> _animations;
};


#endif //ATOMGAME_ANIMATION_H
