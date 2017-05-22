#ifndef ATOMGAME_PROGRAMMABLEOBJECT_H
#define ATOMGAME_PROGRAMMABLEOBJECT_H


#include "PhysicalObject.h"
#include "VCPU/Interpreter/VCPU.h"
#include "tinyxml2.h"

class CustomObject : public PhysicalObject
{
private:
    VCPU *proc;

    CustomObject (const CustomObject &);
public:
    CustomObject (int x, int y, int sizeX, int sizeY, const char *file);

    ~CustomObject ();

    CustomObject clone () const;

    virtual Position tick ();


};


#endif //ATOMGAME_PROGRAMMABLEOBJECT_H
