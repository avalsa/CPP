//
// Created by sl on 06.04.17.
//

#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>
#include <dlfcn.h>
#include "objects/Player.h"
#include "model/Model.h"
#include "view/View.h"
#include "plugins/plugin/Plugin.h"


int main (int argc, char **argv)
{
    std::string initFileName = "log4cpp.properties";
    log4cpp::PropertyConfigurator::configure (initFileName);

    std::vector<Plugin *> plugins;
    for (int i = 1; i < argc; i++)
    {
        const char *so = argv[i];
        if (void *handle = dlopen (argv[i], RTLD_LAZY))
        {
            if (Plugin *(*create) () = (Plugin *(*) ()) dlsym (handle, "create"))
                plugins.push_back (create ());
        } else
            std::cout << dlerror () << '\n';

    }
    Model model;

    model.startGame ();

    View view (&model, 600, 400);
    Controller controller (&model, &view);

    for (std::vector<Plugin *>::iterator i = plugins.begin (); i != plugins.end (); i++)
        (*i)->start (&model, &controller, &view);

    while (!controller.isEnd ())
    {
        controller.tick ();
        model.tick ();
        if (!view.tick ()) return 0;
        for (std::vector<Plugin *>::iterator i = plugins.begin (); i != plugins.end (); i++)
            (*i)->tick ();
    }
}
