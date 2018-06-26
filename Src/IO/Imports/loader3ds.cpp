#include "loader3ds.h"

#include <iostream>

#include "Core/Material/material.h"

using namespace std;

Loader3ds::Loader3ds()
{
    this->currenScene = NULL;
    this->currentObject = NULL;
    this->defaultMaterial = NULL;

}

Scene *Loader3ds::Load(string fileName, Material *_defaultMaterial, float sizeCoeff = 1)
{
    this->defaultMaterial = _defaultMaterial;
    this->sizeCoefficient = sizeCoeff;

    this->currenScene = new Scene();

    this->ProcessFile(fileName);

    return this->currenScene;
}

void Loader3ds::User3dVert(float x, float y, float z)
{
    this->currentObject->Vertexes.push_back( Point3D( x * sizeCoefficient, y * sizeCoefficient, z * sizeCoefficient) );
}

void Loader3ds::User3dFace(unsigned short A, unsigned short B, unsigned short C, unsigned short Flags)
{
    Face *face = new Face(this->currentObject, A, B, C, defaultMaterial);

    Point3D p1 = this->currentObject->Vertexes[B] - this->currentObject->Vertexes[A];
    Point3D p2 = this->currentObject->Vertexes[C] - this->currentObject->Vertexes[A];

    face->normal = (p1 * p2).ToVector3D( true );

    this->currentObject->Faces.push_back( face );
}

void Loader3ds::UserObjName( string Name )
{
    this->currentObject = new Obj( Name );
    //Obj o = *this->currentObject;
    this->currenScene->Objects.push_back( this->currentObject );
}
