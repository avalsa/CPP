//
// Created by sl on 06.04.17.
//


#include "View.h"


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

    //all presses we need
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        controller->onRightKeyPress();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        controller->onLeftKeyPress();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        controller->onUpKeyPress();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        controller->onDownKeyPress();

    //proccess all objs we know
    window.clear();

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
                wall.setPosition(i * 20.f - offsetY, j * 20.f - offsetX);
                window.draw(wall);
            }


    sf::CircleShape playerShape(30.f);
    playerShape.setFillColor(sf::Color::Cyan);
    playerShape.setPosition(player.getY()-offsetY, player.getX()-offsetX); //yes, so because of rotate
    window.draw(playerShape);

    window.display();

    sf::sleep(sf::milliseconds(100));
    return 1;

}

void View::ShowGameOver() {

}

void View::PlayerWin() {

}

View::View(Model *model, Controller *controller, int height, int width):
        model(model),
        controller(controller),
        window(sf::VideoMode(width, height), "AtomGame"),
        offsetX(0),
        offsetY(0)
{
    sf::View view = window.getDefaultView();
    view.setCenter(0, 0);
    view.rotate(90.f);

    window.setView(view);
    logger.info("View init");
}
