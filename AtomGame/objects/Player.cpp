//
// Created by sl on 06.04.17.
//

#include "Player.h"

Player::Player (int x, int y, int sizex, int sizey) : Actor (x, y, sizex, sizey)
{

}

PhysicalObject::Position Player::tick ()
{
    PhysicalObject::Position pos = PhysicalObject::tick ();
    pos.x += _dx;
    pos.y += _dy;
    _dx = 0;
    _dy = 0;
    return pos;
}

void Player::setDx (int _dx)
{
    Player::_dx = _dx;
}

void Player::setDy (int _dy)
{
    Player::_dy = _dy;
}
