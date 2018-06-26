#ifndef LOADER3DS_H
#define LOADER3DS_H

#include "IO/Imports/c3ds/3dsFileLoader.h"
#include "Core/Objects/scene.h"
#include "Core/Objects/obj.h"

using namespace std;

class Loader3ds : public C3dsFileLoader
{
private:
    Scene* currenScene;
    Obj* currentObject;
    float sizeCoefficient;

public:
    Material *defaultMaterial;
    Loader3ds();
    Scene* Load(string fileName, Material *_defaultMaterial, float sizeCoeff);
protected:
    void User3dVert( float x, float y, float z );
    void User3dFace( unsigned short A, unsigned short B, unsigned short C, unsigned short Flags );
    void UserObjName( string Name );

};

#endif // LOADER3DS_H
