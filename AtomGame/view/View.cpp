//
// Created by sl on 06.04.17.
//


#include "View.h"
#include "AnimationFactory.h"
#include "SpriteFactory.h"
#include "ScorePanel.h"
#include "Sounds.h"
#include "../objects/Bot.h"
#include "HealthPanel.h"


log4cpp::Category &View::logger = log4cpp::Category::getInstance (typeid (View).name ());

int View::tick ()     // 1 - window is open, 0 - closed, todo also better to make named const and ret it
{
    logger.info ("View tick");
    if (!window.isOpen ()) return 0;

// get all events we are interested in..
    sf::Event event;
    while (window.pollEvent (event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close ();
            return 0;
        }
    }


//background sounds
    static sf::Sound * gomus = nullptr;
    static sf::Music * music = nullptr;
    if (model->isGameOver())
    {
        music->setVolume(music->getVolume() - music->getVolume() / 30);
        static int e;
        if (!gomus)
        {
            gomus = Sounds::getGameOverSound();
            e = 0;
            gomus->play();
        }
        if (e < 80) e++;
        showGameOver(model->getPlayer().getLives(), e == 80);
        showPlayerStat();
        window.display();
        return 1;
    }
    else
    {
        if (gomus)
        {
            gomus->stop();
            music->setVolume(100.f);
            music->setPlayingOffset(sf::seconds(0));
            gomus = nullptr;
        }
        if (!music)
        {
            music = Sounds::getMainMusic();
            music->setLoop(true);
            music->play();
        }
    }

//process all objs we know
    Player player = model->getPlayer ();
    offsetX = player.getX (); //for map moving
    offsetY = player.getY ();

//draw background
    clear();

//draw blocks
    for (std::vector<PhysicalObject *>::const_iterator i = model->getObjs ().cbegin ();
         i != model->getObjs ().cend (); ++i) {
        if (!isVisible(*i)) continue;
        switch ((*i)->type()) {
            case PhysicalObject::BlockType::Solid:
                if ((*i)->getSizeX() >= (*i)->getSizeY())
                    drawObject(SpriteFactory::getSolidBlockSprite().get(), *i, 0, 1);
                else
                {
                    auto s = SpriteFactory::getSolidBlockSprite();
                    s->rotate(90.f);
                    drawObject(s.get(), *i, 1, 0);
                }
                break;
            case PhysicalObject::Deadly:
                if ((*i)->getSizeX() >= (*i)->getSizeY())
                    drawObject(SpriteFactory::getDeadlyBlockSprite().get(), *i, 0, 1);
                else
                {
                    auto s = SpriteFactory::getDeadlyBlockSprite();
                    s->rotate(90.f);
                    drawObject(s.get(), *i, 1, 0);
                }
                break;
            case PhysicalObject::Respawn:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getRespawnAnimation();
                    a->setAnimationType(Animation::AnimationType::None);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = block_animations[*i]->getNextSprite(PhysicalObject::Direction::Right);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::Portal:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getTeleportAnimation();
                    a->setAnimationType(Animation::AnimationType::None);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = block_animations[*i]->getNextSprite(PhysicalObject::Direction::Right);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::MapChange:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getMapChangeAnimation();
                    a->setAnimationType(Animation::AnimationType::None);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = block_animations[*i]->getNextSprite(PhysicalObject::Direction::Right);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::Player:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getPlayerAnimation();
                    a->setAnimationType(Animation::AnimationType::Stand);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = getActionSprite(dynamic_cast<const Actor*>(*i), block_animations[*i]);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::Coin:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getCoinAnimation();
                    a->setAnimationType(Animation::AnimationType::None);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = block_animations[*i]->getNextSprite(PhysicalObject::Direction::Right);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::Bot:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getBotAnimation();
                    a->setAnimationType(Animation::AnimationType::Stand);
                    block_animations[*i] = a;
                } else {
                    sf::Sprite s = getActionSprite(dynamic_cast<const Actor*>(*i), block_animations[*i]);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::Bullet:
                auto s = SpriteFactory::getBulletSprite();
                Bullet * b = dynamic_cast<Bullet*>(*i);
                if (b->getDirection() == PhysicalObject::Direction::Left)
                    s->rotate(180.f);
                drawObject(s.get(), *i, 1, 1);
                break;

        }
    }

//draw nonObjAnims
    if (_tempAnim.size())
    {
        std::vector<struct AnimInfo>::iterator i = _tempAnim.begin ();
        std::vector<struct AnimInfo>::iterator* prev = nullptr;
        while (i != _tempAnim.end())
        {
            if ( 1.f * i->_anim->getCountFrames() / i->_anim->getFrameRate() - 10 < i->_left)
            {
                delete i->_anim;
                delete i->_obj;
                _tempAnim.erase(i);
                i = (prev == nullptr) ? _tempAnim.begin () : *prev;
            }
            else
            {
                i->_left++;
                sf::Sprite s = i->_anim->getNextSprite(i->_obj->getLookDirection());
                drawObject(&s, i->_obj, 1, 1);
                window.draw(s);
                i++;
            }
            prev = &i;
        }
    }

    showPlayerStat();

//finish
    window.display ();
    return 1;
}

void View::showGameOver (bool isRespawnable, bool isShow)
{
    logger.warn("Game over");
    sf::RectangleShape s(sf::Vector2f(window.getSize()));
    s.setPosition(-(int)window.getSize().x / 2,  -(int)window.getSize().y / 2);
    s.setFillColor(sf::Color(0, 0, 1, 10));
    window.draw(s);

    if (isShow)
    {
        std::shared_ptr<sf::Sprite> e;
        if (isRespawnable)
            e = SpriteFactory::getGameOverRestartSprite();
        else
            e = SpriteFactory::getGameOverSprite();
        e->setPosition(-e->getLocalBounds().width / 2, 0);
        window.draw(*e);
    }
}

View::View (Model *model, int height, int width) :
        model (model),
        window (sf::VideoMode (width, height), "AtomGame"),
        offsetX (0),
        offsetY (0), backgroundType(BackgroundType::City2),
        _playerAnimation (AnimationFactory::getPlayerAnimation ()),
        _tempAnim(std::vector<struct AnimInfo>())
{

    sf::View view = window.getDefaultView ();
    view.setCenter (0, 0);

    window.setView (view);
    logger.info ("View init");
}

bool View::isVisible(const PhysicalObject* obj) const
{
    const int pl_x = model->getPlayer().getX(); const int pl_y = model->getPlayer().getY();
    const int obj_x = obj->getX(); const int obj_y = obj->getY();
    const int obj_s_x = obj->getSizeX(); const int obj_s_y = obj->getSizeY();
    return !(std::abs(pl_x - obj_x) > window.getSize().x/2
             && std::abs(pl_x - (obj_x + obj_s_x)) > window.getSize().x/2
             && ! (pl_x > obj_x && pl_x < obj_x + obj_s_x)
             &&
             std::abs(pl_y - obj_y) > window.getSize().y/2
             && std::abs(pl_y - (obj_y + obj_s_y)) > window.getSize().y/2
             && ! (pl_y > obj_y && pl_y < obj_y + obj_s_y)
    );
}

void View::drawObject(sf::Sprite *sprite, PhysicalObject *object, bool scaleX, bool scaleY) {
    if (scaleY) {
        float scaleY = 1.f * object->getSizeY() / sprite->getGlobalBounds().height;
        sprite->setScale(1.f, scaleY);
    }
    if (scaleX)
    {
        float scaleX = 1.f * object->getSizeX() / sprite->getGlobalBounds().width;
        sprite->scale(scaleX, 1.f);
    }
    if (scaleX && scaleY)
    {
        sprite->setPosition(object->getX() - offsetX, object->getY() - offsetY);
        window.draw (*sprite);
        return;
    }
    if (scaleY) {
        int cnt = object->getSizeX() / sprite->getGlobalBounds().width;
        for (int j = 0; j < std::max(cnt, 1); j++) {
            sprite->setPosition(object->getX() + j * sprite->getGlobalBounds().width - offsetX,
                                object->getY() - offsetY);
            window.draw(*sprite);
        }
        return;
    }
    if (scaleX) {
        int cnt = object->getSizeY() / sprite->getGlobalBounds().height;
        for (int j = 0; j < std::max(cnt, 1); j++) {
            sprite->setPosition(object->getX() + sprite->getGlobalBounds().width  - offsetX,
                                object->getY() + j * sprite->getGlobalBounds().height - offsetY);
            window.draw(*sprite);
        }

    }
}

void View::changeMap(const char *string)
{
    for (auto anim : block_animations)
        delete anim.second;
    block_animations.clear();
    if (string == nullptr)
        logger.warn("Try to change map from nullptr");
    else {
        logger.warn("Change map to \"%s\"", string);
        if (!strcmp(string, "New"))
            backgroundType = BackgroundType::City1;
        if (!strcmp(string, "Init"))
            backgroundType = BackgroundType::City2;
    }
    block_animations.clear();
}

void View::clear() {
    int k = 3; //>=1
    int initY = -1000;
    int initX = 0;
    std::shared_ptr<sf::Sprite> bg;
    bg = SpriteFactory::getBackgroundSprite(backgroundType);
    int sizeX = (int)bg->getLocalBounds().width;
    int sizeY = (int)bg->getLocalBounds().height;
    int a = ( ( offsetX / k - initX ) / sizeX ) * sizeX + initX;
    if (offsetX < 0) a-=sizeX;
    int b = initY;

    switch(backgroundType)
    {
        case BackgroundType::City1:
            window.clear(sf::Color::Black);
            break;
        case  BackgroundType::City2:
            if (offsetY / k > initY + sizeY / 2) window.clear(sf::Color::Black);
            else window.clear(sf::Color(80, 136, 135));
            break;
    }

    bg->setPosition(a - offsetX / k, b - offsetY / k);
    window.draw(*bg);
    if (offsetX / k - a < window.getSize().x/2)
    {
        bg->setPosition(a - sizeX - offsetX / k, b - offsetY / k);
        window.draw(*bg);
    }
    if (sizeX - (offsetX / k - a) < window.getSize().x/2)
    {
        bg->setPosition(a + sizeX - offsetX / k, b - offsetY / k);
        window.draw(*bg);
    }
}

void View::showPlayerWin()
{

}

void View::onCoinPick()
{
    Sounds::getCoinPickSound()->play();
}

void View::onShot() {
    Sounds::getShotSound()->play();
}

sf::Sprite View::getActionSprite(const Actor *pActor, Animation *&pAnimation) {
    sf::Sprite ret;
    if (pActor->isOnGround ())
    {
        if (pActor->isMoving ())
        {
            if (pAnimation->getAnimationType () != Animation::AnimationType::Move)
                pAnimation->setAnimationType (Animation::AnimationType::Move);
            ret = pAnimation->getNextSprite (pActor->getLookDirection ());
        } else
        {
            if (pAnimation->getAnimationType () != Animation::AnimationType::Stand)
                pAnimation->setAnimationType (Animation::AnimationType::Stand);
            ret = pAnimation->getNextSprite (pActor->getLookDirection ());
        }
    } else
    {
        if (pAnimation->getAnimationType () != Animation::AnimationType::Jump)
            pAnimation->setAnimationType (Animation::AnimationType::Jump);
        ret = pAnimation->getNextSprite (pActor->getLookDirection ());
    }
    ret.setPosition (pActor->getX () - offsetX, pActor->getY () - offsetY);
    return ret;
}

void View::onDieBot(Actor* o)
{
    Animation* a = AnimationFactory::getBotAnimation();
    a->setAnimationType(Animation::AnimationType::Die);
    _tempAnim.push_back(AnimInfo(a, o));
}

void View::showPlayerStat()
{
//draw score
    static ScorePanel scorePanel;
    scorePanel.setScore(model->getPlayer().getScore());
    scorePanel.draw(&window);

//draw hp
    static HealthPanel healthPanel;
    healthPanel.setHealth(model->getPlayer().getLives());
    healthPanel.draw(&window);
}

View::~View()
{
    for (auto anim : block_animations)
        delete anim.second;
    for (auto i : _tempAnim)
    {
        delete i._anim;
        delete i._obj;
    }
}

View::AnimInfo::AnimInfo(Animation *anim, Actor* obj) :
        _anim(anim), _obj(obj), _left(0)
{}
