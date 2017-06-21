//
// Created by sl on 16.06.17.
//

#include <cstring>
#include "Sounds.h"

log4cpp::Category &Sounds::logger = log4cpp::Category::getInstance (typeid (Sounds).name ());

sf::Sound* Sounds::getCoinPickSound() {
    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    if (buffer.getDuration() == sf::Time::Zero)
        loadSound("coin.wav", &buffer, &sound);
    return &sound;
}

sf::Sound *Sounds::getGameOverSound() {
    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    if (buffer.getDuration() == sf::Time::Zero)
        loadSound("gameover.wav", &buffer, &sound);
    return &sound;
}

sf::Sound *Sounds::getShotSound() {
    static sf::SoundBuffer buffer;
    static sf::Sound sound;
    if (buffer.getDuration() == sf::Time::Zero)
        loadSound("shot.wav", &buffer, &sound);
    return &sound;
}

sf::Music *Sounds::getMainMusic() {
    static sf::Music music;
    if (music.getDuration() == sf::Time::Zero)
        loadMusic("main.ogg", &music);
    return &music;
}

void Sounds::loadSound(const char *file, sf::SoundBuffer *buf, sf::Sound *snd)
{
    char prefix[80] = "view/res/";
    if (!buf->loadFromFile(strcat(prefix, file)))
    {
        logger.warn("Problem in loading sound \"%s\"", file);
        return;
    }
    logger.info("Sound \"%s\" loaded successful", file);
    snd->setBuffer(*buf);
}

void Sounds::loadMusic(const char *file, sf::Music *mus)
{
    char prefix[80] = "view/res/";
    if (!mus->openFromFile(strcat(prefix,  file)))
    {
        logger.warn("Problem in loading music \"%s\"", file);
        return;
    }
    logger.info("Music \"%s\" loaded successful", file);
}
