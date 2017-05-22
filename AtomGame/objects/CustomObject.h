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

protected:

    void load (tinyxml2::XMLElement *block);
public:
    CustomObject (int x, int y, int sizeX, int sizeY, const char *file);

    CustomObject (int x, int y, int sizeX, int sizeY, tinyxml2::XMLElement *block = nullptr);

    CustomObject (int x, int y, int sizeX, int sizeY, BlockType type);

    virtual ~CustomObject ();

    CustomObject clone () const;

    virtual Position tick ();


};


#endif //ATOMGAME_PROGRAMMABLEOBJECT_H
