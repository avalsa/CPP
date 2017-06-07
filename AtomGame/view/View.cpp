//
// Created by sl on 06.04.17.
//


#include "View.h"
#include "AnimationFactory.h"
#include "SpriteFactory.h"


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

//process all objs we know
    window.clear (sf::Color::Black);

    Player player = model->getPlayer ();
    offsetX = player.getX (); //for map moving
    offsetY = player.getY ();

//    GameField gameField = model->getGameField ();
//    int x = gameField.getWidth ();
//    int y = gameField.getHeight ();
//
//    sf::RectangleShape wall (sf::Vector2f (20.f, 20.f));
//    for (int i = 0; i < x; ++i)
//        for (int j = 0; j < y; ++j)
//            if (gameField.getCell (i, j))
//            {
//                wall.setPosition (j * 20.f - offsetX, -i * 20.f - offsetY);
//                window.draw (wall);
//            }

    model->

//draw background
    int k = 3; //>=1
    int initY = -1000;
    int initX = 0;
    auto bg = SpriteFactory::getBackgroundSprite();
    int sizeX = (int)bg->getLocalBounds().width;
    int sizeY = (int)bg->getLocalBounds().height;
    int a = ( ( offsetX / k - initX ) / sizeX ) * sizeX + initX;
    if (offsetX < 0) a-=sizeX;
    int b = initY;
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
    for (std::vector<PhysicalObject *>::const_iterator i = model->getBlocks ().cbegin ();
         i != model->getBlocks ().cend (); ++i)
    {
        if (!isVisible(*i)) continue;
        switch ((*i)->type ())
        {
            case PhysicalObject::BlockType::Solid:
                drawObject(SpriteFactory::getSolidBlockSprite().get(), *i, 0, 1);
                break;
            case PhysicalObject::Deadly:

                break;
            case PhysicalObject::Respawn:

                break;
            case PhysicalObject::Portal:
                if (block_animations[*i] == nullptr) {
                    Animation *a = AnimationFactory::getTeleportAnimation();
                    a->setAnimationType(Animation::AnimationType::None);
                    block_animations[*i] = a;
                }
                else {
                    sf::Sprite s = block_animations[*i]->getNextSprite(PhysicalObject::Direction::Right);
                    drawObject(&s, *i, 1, 1);
                }
                break;
            case PhysicalObject::MapChange:

                break;
            case PhysicalObject::Player:

                break;
        }
    }

//finish
    window.display ();
    sf::sleep (sf::milliseconds (10));
    return 1;
}

void View::ShowGameOver ()
{

}

void View::PlayerWin ()
{

}

View::View (Model *model, int height, int width) :
        model (model),
        window (sf::VideoMode (width, height), "AtomGame"),
        offsetX (0),
        offsetY (0),
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
             ||
             std::abs(pl_y - obj_y) > window.getSize().y/2
             && std::abs(pl_y - (obj_y + obj_s_y)) > window.getSize().y/2
             && ! (pl_y > obj_y && pl_y < obj_y + obj_s_y)
    );
}

void View::drawObject(sf::Sprite *sprite, PhysicalObject *object, bool scaleX, bool scaleY) {
    if (scaleY) {
        float scaleY = 1.f * object->getSizeY() / sprite->getLocalBounds().height;
        sprite->setScale(1.f, scaleY);
    }
    if (scaleX)
    {
        float scaleX = 1.f * object->getSizeX() / sprite->getLocalBounds().width;
        sprite->scale(scaleX, 1.f);
    }
    if (scaleX && scaleY)
    {
        sprite->setPosition(object->getX() - offsetX, object->getY() - offsetY);
        window.draw (*sprite);
    }
    else {
        int cnt = object->getSizeX() / sprite->getLocalBounds().width;
        for (int j = 0; j < std::max(cnt, 1); j++) {
            sprite->setPosition(object->getX() + j * sprite->getLocalBounds().width - offsetX,
                                object->getY() - offsetY);
            window.draw(*sprite);
        }
    }
}

