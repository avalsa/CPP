//
// Created by sl on 27.04.17.
//

#ifndef ATOMGAME_ANIMATION_H
#define ATOMGAME_ANIMATION_H

#include <log4cpp/Category.hh>
#include <SFML/Graphics.hpp>
#include "../objects/PhysicalObject.h"

class Animation
{
public:

    enum AnimationType
    { //not the same as objects/action
        Move, Jump, Stand, Die
    };

    AnimationType getAnimationType () const;

    void setAnimationType (AnimationType type);

    Animation (const char *, float frameRate); //file name, frameRate << 1

    ~Animation ();

    const sf::Sprite getNextSprite (PhysicalObject::Direction direction);

private:
    enum Files
    {
        PLAYER, BOT
    };
    static std::map<const char *, int> files;

    static log4cpp::Category &logger;

    struct FrameSequence
    {
        int _FrameCount;
        int _init_x; //init point for frame offset
        int _init_y;
        int _size_x; //size of one frame
        int _size_y;

        FrameSequence (int frameCount, int init_x, int init_y, int size_x, int size_y);
    };

    float _frameRate;
    float _currentFrame;
    sf::Texture _texture;
    sf::Sprite _sprite;
    AnimationType _animationType;

    std::map<AnimationType, FrameSequence *> _animations;
};


#endif //ATOMGAME_ANIMATION_H
