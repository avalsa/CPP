//
// Created by sl on 06.04.17.
//

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <dlfcn.h>
#include "objects/Player.h"
#include "model/Model.h"
#include "plugins/plugin/Plugin.h"


int main (int argc, char **argv)
{
    std::string initFileName = "log4cpp.properties";
    log4cpp::PropertyConfigurator::configure (initFileName);
    std::vector<std::pair<void *, Plugin *>> plugins;
    for (int i = 1; i < argc; i++)
    {
        const char *so = argv[i];
        if (void *handle = dlopen (argv[i], RTLD_LAZY))
        {
            if (Plugin *(*create) () = (Plugin *(*) ()) dlsym (handle, "create"))
                plugins.push_back (std::pair<void *, Plugin *> (handle, create ()));
            else
                dlclose (handle);
        } else
            std::cout << dlerror () << '\n';

    }
    Model model;

    model.startGame ();

    View view (&model, 600, 400);
    Controller controller (&model, &view);
    model.setController(&controller);

    for (std::vector<std::pair<void *, Plugin *>>::iterator i = plugins.begin (); i != plugins.end (); i++)
        i->second->start (&model, &controller, &view);
    while (!controller.isEnd ())
    {
        const clock_t begin_time = clock();
        controller.tick ();
        model.tick ();
        if (!view.tick ()) break;
        for (std::vector<std::pair<void *, Plugin *>>::iterator i = plugins.begin (); i != plugins.end (); i++)
            i->second->tick ();
        int time =  (int)(clock () - begin_time);
        sf::sleep(sf::microseconds (10000 - time));
    }

    for (std::vector<std::pair<void *, Plugin *>>::const_iterator i = plugins.cbegin (); i != plugins.cend (); i++)
    {
        delete i->second;
        dlclose (i->first);
    }
}
