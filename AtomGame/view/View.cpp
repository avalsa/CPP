//
// Created by sl on 06.04.17.
//


#include "View.h"
#include "AnimationFactory.h"
#include "SpriteFactory.h"
#include "ScorePanel.h"
#include "Sounds.h"
#include "../objects/Bot.h"


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

//background sound
    static sf::Music * music = nullptr;
    if (!music)
    {
        music = Sounds::getMainMusic();
        music->setLoop(true);
        music->play();
    }

//check game end
    if (model->isGameOver())
    {
        static sf::Sound * gomus = nullptr;
        music->setVolume(music->getVolume() - music->getVolume() / 30);
        if (!gomus)
        {
            gomus = Sounds::getGameOverSound();
            gomus->play();
        }

        showGameOver();
        window.display();
        sf::sleep(sf::milliseconds(10));
        return 1;
    }

//process all objs we know
    Player player = model->getPlayer ();
    offsetX = player.getX (); //for map moving
    offsetY = player.getY ();

//draw background
    clear();

//here we draw player
    sf::Sprite playerSprite;
    if (player.isOnGround ())
    {
        if (player.isMoving ())
        {
            if (_playerAnimation->getAnimationType () != Animation::AnimationType::Move)
                _playerAnimation->setAnimationType (Animation::AnimationType::Move);
            playerSprite = _playerAnimation->getNextSprite (player.getLookDirection ());
        } else
        {
            if (_playerAnimation->getAnimationType () != Animation::AnimationType::Stand)
                _playerAnimation->setAnimationType (Animation::AnimationType::Stand);
            playerSprite = _playerAnimation->getNextSprite (player.getLookDirection ());
        }
    } else
    {
        if (_playerAnimation->getAnimationType () != Animation::AnimationType::Jump)
            _playerAnimation->setAnimationType (Animation::AnimationType::Jump);
        playerSprite = _playerAnimation->getNextSprite (player.getLookDirection ());
    }
    playerSprite.setPosition (player.getX () - offsetX, player.getY () - offsetY);

    window.draw (playerSprite);

//draw blocks
    static std::map<PhysicalObject*, Animation*> block_animations;
    for (std::vector<PhysicalObject *>::const_iterator i = model->getObjs ().cbegin ();
         i != model->getObjs ().cend (); ++i) {
        if (!isVisible(*i)) continue;
        switch ((*i)->type()) {
            case PhysicalObject::BlockType::Solid:
                drawObject(SpriteFactory::getSolidBlockSprite().get(), *i, 0, 1);
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
//draw score
    static ScorePanel scorePanel;
    scorePanel.setScore(player.getScore());
    scorePanel.draw(&window);

//finish
    window.display ();
//    sf::sleep (sf::milliseconds (10));
    return 1;
}

void View::showGameOver ()
{
    logger.warn("Game over");
    static int i = 0;
    if ((++i) > 80 ) i = 80;
    sf::RectangleShape s(sf::Vector2f(window.getSize()));
    s.setPosition(-(int)window.getSize().x / 2,  -(int)window.getSize().y / 2);
    s.setFillColor(sf::Color(0, 0, 1, 10));
    window.draw(s);

    if (i == 80)
    {
        auto e = SpriteFactory::getGameOverSprite();
        e->setPosition(-e->getLocalBounds().width / 2, 0);
        window.draw(*e);
    }
}

View::View (Model *model, int height, int width) :
        model (model),
        window (sf::VideoMode (width, height), "AtomGame"),
        offsetX (0),
        offsetY (0), backgroundType(BackgroundType::City2),
        _playerAnimation (AnimationFactory::getPlayerAnimation ())
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
            sprite->setPosition(object->getX()  - offsetX,
                                object->getY() + j * sprite->getGlobalBounds().height - offsetY);
            window.draw(*sprite);
        }

    }
}

void View::changeMap(const char *string) {
    if (string == nullptr)
        logger.warn("Try to change map from nullptr");
    else {
        logger.warn("Change map to \"%s\"", string);
        if (!strcmp(string, "New"))
            backgroundType = BackgroundType::City1;
        if (!strcmp(string, "Init"))
            backgroundType = BackgroundType::City2;
    }
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

