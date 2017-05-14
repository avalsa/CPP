#ifndef ATOMGAME_PROGRAMMABLEOBJECT_H
#define ATOMGAME_PROGRAMMABLEOBJECT_H


#include "PhysicalObject.h"
#include "VCPU/Interpreter/VCPU.h"

class ProgrammableObject : public PhysicalObject
{
public:
    virtual Position tick ();

private:
    VCPU proc;
public:
    ProgrammableObject (int x, int y, int sizeX, int sizeY, const char *file);

};


#endif //ATOMGAME_PROGRAMMABLEOBJECT_H
