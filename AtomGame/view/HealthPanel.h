//
// Created by sl on 24.06.17.
//

#ifndef ATOMGAME_HEALPHPANEL_H
#define ATOMGAME_HEALPHPANEL_H


#include <SFML/Graphics/RenderWindow.hpp>

class HealthPanel
{
public:
    HealthPanel(int = 0);

    void setHealth(int);

    void draw(sf::RenderWindow*);

private:
    int _hp;
};


#endif //ATOMGAME_HEALPHPANEL_H
