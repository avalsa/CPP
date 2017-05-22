//
// Created by sl on 06.04.17.
//

#include "Player.h"

Player::Player (int x, int y, int sizeX, int sizeY) : Actor (x, y, sizeX, sizeY), _respX (x), _respY (y)
{

}

void Player::respawn ()
{
    _x = _respX;
    _y = _respY;
}

void Player::collided (const PhysicalObject &source, PhysicalObject::Axis relativeLocation)
{
    switch (source.type ())
    {
        case PhysicalObject::BlockType::Deadly :
            respawn ();
            break;
        case PhysicalObject::BlockType::Respawn :
            _respX = _x;
            _respY = _y;
            Actor::collided (source, relativeLocation);
            break;
        default:
            Actor::collided (source, relativeLocation);
            break;
    }
}
