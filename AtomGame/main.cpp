//
// Created by sl on 06.04.17.
//

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include "objects/Player.h"
#include "model/Model.h"
#include "view/View.h"


int main()
{
    std::string initFileName = "log4cpp.properties";
    log4cpp::PropertyConfigurator::configure(initFileName);

    Model model;

    model.startGame();

    View view (&model, 600, 400);
    Controller controller (&model, &view);
    for (;;) {
        controller.tick ();
        model.tick ();
        if (!view.tick()) return 0;
    }
}
