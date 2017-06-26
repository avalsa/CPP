//
// Created by sl on 24.06.17.
//

#include "HealthPanel.h"
#include "SpriteFactory.h"

HealthPanel::HealthPanel(int h) : _hp(h)
{}

void HealthPanel::setHealth(int hp)
{
    _hp = hp;
}

void HealthPanel::draw(sf::RenderWindow *window) {
    auto s_o = SpriteFactory::getHeartSprite();
    for (int i = 0; i < _hp; i++) {
        s_o->setPosition(
                -(int) (window->getSize().x) / 2 + i * s_o->getGlobalBounds().width,
                -(int) (window->getSize().y) / 2);
        window->draw(*s_o);
    }
}