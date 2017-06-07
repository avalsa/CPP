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

class SpriteFactory
{

public:

    enum ObjectType
    { SolidBlock, DeadlyBlock, Background };

    static std::shared_ptr<sf::Sprite> getSprite(ObjectType objectType);

    static std::shared_ptr<sf::Sprite> getSolidBlockSprite();

    static std::shared_ptr<sf::Sprite> getBackgroundSprite();

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
