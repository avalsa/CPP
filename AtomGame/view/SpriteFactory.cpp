//
// Created by sl on 04.06.17.
//


#include "SpriteFactory.h"

std::map<SpriteFactory::ObjectType, std::pair<const char*, const char*>> SpriteFactory::_files = {
        {ObjectType::SolidBlock, {"platform.xml", "platform.png"}},
        {ObjectType::Background, {"background1.xml", "background1.png"}},
};

std::vector<std::shared_ptr<sf::Texture>> SpriteFactory::_textures = std::vector<std::shared_ptr<sf::Texture>>();

std::map<std::shared_ptr<SpriteFactory::ObjectType>, std::shared_ptr<sf::Sprite>, SpriteFactory::Comp>
        SpriteFactory::_sprites = std::map<std::shared_ptr<SpriteFactory::ObjectType>, std::shared_ptr<sf::Sprite>, SpriteFactory::Comp>();

log4cpp::Category &SpriteFactory::logger = log4cpp::Category::getInstance (typeid (SpriteFactory).name());

SpriteFactory::SpriteFactory()
{}

std::shared_ptr<sf::Sprite> SpriteFactory::getSprite(ObjectType objectType) {
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

std::shared_ptr<sf::Sprite> SpriteFactory::getBackgroundSprite() {
    return getSprite(ObjectType::Background);
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
    if (!strcmp(str, "SolidBlock"))
        return SolidBlock;
    if (!strcmp(str, "DeadlyBlock"))
        return DeadlyBlock;
    if (!strcmp(str, "Background"))
        return Background;
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
