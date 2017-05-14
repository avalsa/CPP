//
// Created by svuatoslav on 5/14/17.
//

#include "ProgrammableObject.h"

ProgrammableObject::ProgrammableObject (int x, int y, int sizeX, int sizeY, const char *file) : PhysicalObject (x, y,
                                                                                                                sizeX,
                                                                                                                sizeY)
{
    std::ifstream in (file, std::ios_base::binary);
    if (proc.load (in))
        logger.info ("Loaded program from \"%s\"", file);
    else
        logger.warn ("Failed to load program from \"%s\"", file);
}

PhysicalObject::Position ProgrammableObject::tick ()
{
    proc.setReg (_x, 0);
    proc.setReg (_y, 1);
    proc.setReg (_vx, 2);
    proc.setReg (_vy, 3);
    proc.setReg (_ax, 4);
    proc.setReg (_ay, 5);
    proc.execute ();
    proc.reset ();
    _x = proc.getReg (0);
    _y = proc.getReg (1);
    _vx = proc.getReg (2);
    _vy = proc.getReg (3);
    _ax = proc.getReg (4);
    _ay = proc.getReg (5);
    return PhysicalObject::tick ();
}
