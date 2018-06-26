#ifndef OBJ_H
#define OBJ_H

#include <vector>
#include <string>

#include "face.h"

using namespace std;

class Obj
{
public:
    string Name;
    vector<Point3D> Vertexes;
    vector<Face*> Faces;
    Obj* obj;

    Obj();
    Obj( string name );
    virtual ~Obj();

};

#endif // OBJ_H
