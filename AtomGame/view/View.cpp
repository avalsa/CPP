//
// Created by sl on 06.04.17.
//


#include "View.h"
#include "AnimationFactory.h"


log4cpp::Category& View::logger = log4cpp::Category::getInstance(typeid(View).name());

int View::tick()     // 1 - window is open, 0 - closed, todo also better to make named const and ret it
{
    logger.info("View tick");
    if (!window.isOpen()) return 0;

    //  get all events we are interested in..
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }
    }

    //proccess all objs we know
    window.clear(sf::Color::Blue);

    Player player = model->getPlayer();
    offsetX = player.getX(); //for map moving
    offsetY = player.getY();

    GameField gameField = model->getGameField();
    int x = gameField.getWidth();
    int y = gameField.getHeight();

    sf::RectangleShape wall(sf::Vector2f(20.f, 20.f));
    for (int i = 0; i < x; ++i)
        for (int j = 0; j < y; ++j)
            if (gameField.getCell(i, j)) {
                wall.setPosition (j * 20.f - offsetX, i * 20.f - offsetY);
                window.draw(wall);
            }

//here we draw player
    sf::Sprite playerSprite;
    logger.warn(std::to_string(player.getAction()));
    if (player.isOnGround ())
    {
        if (player.isMoving ())
        {
            if (_playerAnimation->getAnimationType() != Animation::AnimationType::Move)
                _playerAnimation->setAnimationType(Animation::AnimationType::Move);
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

    window.draw(playerSprite);



//draw blocks
    for (std::vector<PhysicalObject *>::const_iterator i = model->getBlocks ().cbegin ();
         i != model->getBlocks ().cend (); ++i)
    {
        sf::RectangleShape obj;
        obj.setSize (sf::Vector2f ((*i)->getSizex (), (*i)->getSizey ()));
        obj.setFillColor (sf::Color::Green);
        obj.setPosition ((*i)->getX () - offsetX, (*i)->getY () - offsetY);
        window.draw (obj);
    }

//    sf::Sprite s;
//
//    sf::Texture t;
//    t.loadFromFile("player.gif");
//
//    s.setTexture(t);
//    s.setTextureRect(sf::IntRect(0, 80, 38, 42));
//    s.setPosition(player.getY()-offsetY, player.getX()-offsetX);
//    window.draw(s);
//finish

    window.display();

    sf::sleep(sf::milliseconds(10));
    return 1;

}

void View::ShowGameOver() {

}

void View::PlayerWin() {

}

View::View (Model *model, int height, int width) :
        model(model),
        window(sf::VideoMode(width, height), "AtomGame"),
        offsetX(0),
        offsetY(0),
        _playerAnimation(AnimationFactory::getPlayerAnimation())
{

    sf::View view = window.getDefaultView();
    view.setCenter(0, 0);

    window.setView(view);
    logger.info("View init");
}

