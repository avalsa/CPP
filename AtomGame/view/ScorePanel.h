//
// Created by sl on 13.06.17.
//

#ifndef ATOMGAME_SCOREPANEL_H
#define ATOMGAME_SCOREPANEL_H

#include <SFML/Graphics/RenderWindow.hpp>

class ScorePanel {

public:
    ScorePanel(int = 0);

    void setScore(int);

    void draw(sf::RenderWindow*);

private:
    int _score;

};


#endif //ATOMGAME_SCOREPANEL_H
