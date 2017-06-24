//
// Created by sl on 04.06.17.
//


#include "SpriteFactory.h"

std::map<SpriteFactory::ObjectType, std::pair<const char*, const char*>> SpriteFactory::_files = {
        {ObjectType::SolidBlock, {"platform.xml", "platform.png"}},
        {ObjectType::DeadlyBlock, {"thorn.xml", "thorn.png"}},
        {ObjectType::Background1, {"background1.xml", "background1.png"}},
        {ObjectType::Background2, {"background2.xml", "background2.png"}},
        {ObjectType::GameOver, {"gameover.xml", "gameover.png"}},
        {ObjectType::Number0, {"number_0.xml", "number_0.png"}},
        {ObjectType::Number1, {"number_1.xml", "number_1.png"}},
        {ObjectType::Number2, {"number_2.xml", "number_2.png"}},
        {ObjectType::Number3, {"number_3.xml", "number_3.png"}},
        {ObjectType::Number4, {"number_4.xml", "number_4.png"}},
        {ObjectType::Number5, {"number_5.xml", "number_5.png"}},
        {ObjectType::Number6, {"number_6.xml", "number_6.png"}},
        {ObjectType::Number7, {"number_7.xml", "number_7.png"}},
        {ObjectType::Number8, {"number_8.xml", "number_8.png"}},
        {ObjectType::Number9, {"number_9.xml", "number_9.png"}},
        {ObjectType::Bullet, {"bullet.xml", "bullet.png"}},
        {ObjectType::Heart, {"heart.xml", "heart.png"}},
        {ObjectType::GameOverRestart, {"gameoverres.xml", "gameoverres.png"}},
};

std::vector<std::shared_ptr<sf::Texture>> SpriteFactory::_textures = std::vector<std::shared_ptr<sf::Texture>>();

std::map<std::shared_ptr<SpriteFactory::ObjectType>, std::shared_ptr<sf::Sprite>, SpriteFactory::Comp>
        SpriteFactory::_sprites = std::map<std::shared_ptr<SpriteFactory::ObjectType>, std::shared_ptr<sf::Sprite>, SpriteFactory::Comp>();

log4cpp::Category &SpriteFactory::logger = log4cpp::Category::getInstance (typeid (SpriteFactory).name());

SpriteFactory::SpriteFactory()
{}

std::shared_ptr<sf::Sprite> SpriteFactory::getSprite(ObjectType objectType)
{
    std::shared_ptr<ObjectType> type(new ObjectType(objectType));
    if (_sprites[type] == nullptr){
        std::pair<const char*, const char*> file = _files[objectType];
        load(file.first, file.second);
    }
    sf::Sprite t = *_sprites[type];
    std::shared_ptr<sf::Sprite> s(new sf::Sprite(t));
    return s;
}

std::shared_ptr<sf::Sprite> SpriteFactory::getSolidBlockSprite()
{
    return getSprite(ObjectType::SolidBlock);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getDeadlyBlockSprite()
{
    return getSprite(ObjectType::DeadlyBlock);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getGameOverSprite()
{
    return getSprite(ObjectType::GameOver);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getBulletSprite() {
    return getSprite(ObjectType::Bullet);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getHeartSprite() {
    return getSprite(ObjectType::Heart);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getGameOverRestartSprite() {
    return getSprite(ObjectType::GameOverRestart);
}

std::shared_ptr<sf::Sprite> SpriteFactory::getNumberSprite(int number)
{
    switch(number)
    {
        case 0: return getSprite(ObjectType::Number0);
        case 1: return getSprite(ObjectType::Number1);
        case 2: return getSprite(ObjectType::Number2);
        case 3: return getSprite(ObjectType::Number3);
        case 4: return getSprite(ObjectType::Number4);
        case 5: return getSprite(ObjectType::Number5);
        case 6: return getSprite(ObjectType::Number6);
        case 7: return getSprite(ObjectType::Number7);
        case 8: return getSprite(ObjectType::Number8);
        case 9: return getSprite(ObjectType::Number9);
    }
}

std::shared_ptr<sf::Sprite> SpriteFactory::getBackgroundSprite(View::BackgroundType bt) {
    switch (bt){
        case View::BackgroundType::City1 :
            return getSprite(ObjectType::Background1);
        case View::BackgroundType::City2 :
            return getSprite(ObjectType::Background2);
    }

}

void SpriteFactory::load(const char *filexml, const char* fileimg)
{
    char prefix[80] = "view/res/";
    if (filexml == nullptr)
    {
        logger.warn ("Trying to load file from nullptr");
        return;
    }
    logger.info ("Loading sprite from \"%s\"", filexml);
    tinyxml2::XMLDocument fs;
    if (int err = fs.LoadFile (strcat(prefix, filexml)))
    {
        logger.warn ("Failed to sprite from \"%s\", errorID = %d", filexml, err);
    }
    else {
        logger.info("\"%s\" parsed", filexml);

        logger.info("Loading texture from file \"%s\"", fileimg);
        std::shared_ptr<sf::Texture> texture(new sf::Texture());
        char prefix[80] = "view/res/";
        if (!texture->loadFromFile(strcat(prefix, fileimg)))
            logger.warn("Problem in loading \"%s\"", fileimg);
        else
        {
            _textures.push_back(texture);
            load(fs, filexml, texture);
        }
    }
}

void SpriteFactory::load(tinyxml2::XMLDocument &xmlDocument, const char *file, std::shared_ptr<sf::Texture> texture)
{
    if(tinyxml2::XMLElement* objs = xmlDocument.FirstChildElement ("Objects"))
    {
        for(tinyxml2::XMLElement* obj = objs->FirstChildElement ("Object"); obj != nullptr; obj = obj->NextSiblingElement ("Action") ) {
            const char* typestr = obj->Attribute("Type");
            if (typestr != nullptr){
                Block block(obj);
                if (block._size_x == -1 || block._size_y == -1 || block._init_x == -1 || block._init_y == -1 )
                    logger.warn("Problem while loading sprite of type \"%s\" in file \"%s\"", typestr, file);
                else {
                    int res;
                    std::shared_ptr<ObjectType> type (new ObjectType(makeObjectType(typestr, res)));
                    if (res) {
                        logger.warn("Problem with type value in \"%s\", ErrorID = %d", file, res);
                        continue;
                    }
                    std::shared_ptr<sf::Sprite> sprite(new sf::Sprite(*texture, sf::IntRect(block._init_x, block._init_y, block._size_x, block._size_y)));
                    _sprites[type] = sprite;
                }
            }
            else
                logger.warn("Type of object is not defined in \"%s\"", file);
        }
    }
    else
        logger.warn ("Sprite file \"%s\" has no sprites", file);
}

SpriteFactory::ObjectType SpriteFactory::makeObjectType(const char *str, int &res)
{
    res = 0;
    if (!strcmp(str, "SolidBlock")) return SolidBlock;
    if (!strcmp(str, "DeadlyBlock")) return DeadlyBlock;
    if (!strcmp(str, "Background1")) return Background1;
    if (!strcmp(str, "Background2")) return Background2;
    if (!strcmp(str, "GameOver")) return GameOver;
    if (!strcmp(str, "Number0")) return Number0;
    if (!strcmp(str, "Number1")) return Number1;
    if (!strcmp(str, "Number2")) return Number2;
    if (!strcmp(str, "Number3")) return Number3;
    if (!strcmp(str, "Number4")) return Number4;
    if (!strcmp(str, "Number5")) return Number5;
    if (!strcmp(str, "Number6")) return Number6;
    if (!strcmp(str, "Number7")) return Number7;
    if (!strcmp(str, "Number8")) return Number8;
    if (!strcmp(str, "Number9")) return Number9;
    if (!strcmp(str, "Bullet")) return Bullet;
    if (!strcmp(str, "Heart")) return Heart;
    if (!strcmp(str, "GameOverRestart")) return GameOverRestart;
    res = 1;
    return SolidBlock;
}

SpriteFactory::Block::Block(tinyxml2::XMLElement *action) :
        _init_x (-1), _init_y (-1), _size_x (-1), _size_y (-1)
{
    if (tinyxml2::XMLElement* place = action->FirstChildElement("Place"))
    {
        if (place->Attribute("X"))
            this->_init_x = place->IntAttribute("X");
        else
            logger.warn("No init X attribute");
        if (place->Attribute("Y"))
            this->_init_y = place->IntAttribute("Y");
        else
            logger.warn("No init Y attribute");
    } else
        logger.warn("No place information");

    if (tinyxml2::XMLElement* size = action->FirstChildElement("Size"))
    {
        if (size->Attribute("X"))
            this->_size_x = size->IntAttribute("X");
        else
            logger.warn("No size X attribute");
        if (size->Attribute("Y"))
            this->_size_y = size->IntAttribute("Y");
        else
            logger.warn("No size Y attribute");
    } else
        logger.warn("No size information");
}

bool SpriteFactory::Comp::operator()(const std::shared_ptr<SpriteFactory::ObjectType> a,
                                     const std::shared_ptr<SpriteFactory::ObjectType> b) const {
    return (*a) < (*b);
}