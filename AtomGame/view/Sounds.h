//
// Created by sl on 16.06.17.
//

#ifndef ATOMGAME_SOUNDS_H
#define ATOMGAME_SOUNDS_H

#include <SFML/Audio.hpp>
#include <log4cpp/Category.hh>
#include <memory>

class Sounds
{
public:
    static sf::Music* getMainMusic();

    static sf::Sound* getCoinPickSound();

    static sf::Sound* getGameOverSound();

private:
    static void loadSound(const char*, sf::SoundBuffer*, sf::Sound*);

    static void loadMusic(const char*, sf::Music*);

    static log4cpp::Category &logger;

};


#endif //ATOMGAME_SOUNDS_H
