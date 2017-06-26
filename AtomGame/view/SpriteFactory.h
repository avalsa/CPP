//
// Created by sl on 04.06.17.
//

#ifndef ATOMGAME_TEXTUREFACTORY_H
#define ATOMGAME_TEXTUREFACTORY_H


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tinyxml2.h>
#include <log4cpp/Category.hh>
#include <memory>
#include "View.h"

class SpriteFactory
{

public:

    enum ObjectType
    { SolidBlock, DeadlyBlock, GameOver,
        Background1, Background2,
        Number0, Number1, Number2, Number3, Number4, Number5, Number6, Number7, Number8, Number9,
        Bullet, Heart, GameOverRestart
    };

    static std::shared_ptr<sf::Sprite> getSprite(ObjectType objectType);

    static std::shared_ptr<sf::Sprite> getSolidBlockSprite();

    static std::shared_ptr<sf::Sprite> getDeadlyBlockSprite();

    static std::shared_ptr<sf::Sprite> getBackgroundSprite(View::BackgroundType );

    static std::shared_ptr<sf::Sprite> getGameOverSprite();

    static std::shared_ptr<sf::Sprite> getNumberSprite(int);

    static std::shared_ptr<sf::Sprite> getBulletSprite();

    static std::shared_ptr<sf::Sprite> getHeartSprite();

    static std::shared_ptr<sf::Sprite> getGameOverRestartSprite();

private:

    struct Comp
    {
        bool operator()(const std::shared_ptr<ObjectType> a, const std::shared_ptr<ObjectType> b) const;
    };

    struct Block{
        int _init_x;
        int _init_y;
        int _size_x;
        int _size_y;
        Block(tinyxml2::XMLElement *action);
    };

    static log4cpp::Category &logger;

    SpriteFactory();

    static std::map<ObjectType, std::pair<const char*, const char*>> _files;

    static std::vector<std::shared_ptr<sf::Texture>> _textures;

    static std::map<std::shared_ptr<ObjectType>, std::shared_ptr<sf::Sprite>, Comp> _sprites;

    static void load(const char *filexml, const char *fileimg);

    static void load(tinyxml2::XMLDocument& xmlDocument, const char *file, std::shared_ptr<sf::Texture> texture);

    static ObjectType makeObjectType(const char* str, int& res);

};


#endif //ATOMGAME_TEXTUREFACTORY_H
