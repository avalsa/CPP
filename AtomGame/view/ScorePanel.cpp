//
// Created by sl on 13.06.17.
//

#include <SFML/Graphics/RectangleShape.hpp>
#include "ScorePanel.h"
#include "SpriteFactory.h"

ScorePanel::ScorePanel(int score) : _score(score)
{}

void ScorePanel::setScore(int score) {
    _score = score;
}

void ScorePanel::draw(sf::RenderWindow* window)
{
    int tens = _score / 10;
    int ones = _score % 10;
    auto s_o = SpriteFactory::getNumberSprite(ones);
    s_o->setPosition(
            (int)(window->getSize().x) / 2 -  s_o->getGlobalBounds().width,
            -(int)(window->getSize().y) / 2);
    window->draw(*s_o);
    if (tens != 0)
    {
        auto s_t = SpriteFactory::getNumberSprite(tens);
        s_t->setPosition(
                (int)(window->getSize().x) / 2 - (s_o->getGlobalBounds().width + s_t->getGlobalBounds().width),
                        -(int)(window->getSize().y) / 2);
        window->draw(*s_t);
    }
}