#ifndef TYPES_H
#define TYPES_H


typedef float Coordinate;

struct Point3D;


struct Vector3D
{
public:
    Coordinate X;
    Coordinate Y;
    Coordinate Z;

    Vector3D();
    Vector3D( Coordinate x, Coordinate y, Coordinate z, bool normalize = false );
    Vector3D( const Point3D &from, const Point3D &to, bool normalize = true );
    Vector3D( const float theta, const float phi );

    void Normalize();

    const Vector3D operator*( const Coordinate& right ) const;
    const Vector3D operator/( const Coordinate& right ) const;
    const Vector3D operator*( const Vector3D& right ) const;
    const Vector3D operator+( const Vector3D& right ) const;
    const Vector3D operator-( const Vector3D& right ) const;
    const Vector3D operator+=( const Vector3D& right );

    const Vector3D Reflect( const Vector3D &normal, bool normalize = true );
    const Point3D ToPoint3D() const;

    static Coordinate Dot(const Vector3D &v1, const Vector3D &v2);
    static Coordinate Dot2(const Vector3D &v1, const Vector3D &v2);
    static Vector3D Reflect( const Vector3D &fall, const Vector3D &normal );

protected:
};

struct Point3D
{
public:
    Coordinate X;
    Coordinate Y;
    Coordinate Z;

    Point3D();
    Point3D( Coordinate x, Coordinate y, Coordinate z );

    Coordinate Length() const;
    Coordinate Length2() const;

    const Point3D operator*( const Point3D &right ) const;
    const Point3D operator/( const Coordinate &right ) const;
    const Point3D operator+( const Vector3D &right ) const;
    const Point3D operator+( const Point3D &right ) const;
    const Point3D operator-( const Point3D &right ) const;

    static Coordinate Dot(const Point3D &p1, const Point3D &p2);
    static Coordinate Length( const Point3D &p1, const Point3D &p2 );
    static Coordinate LengthSquared( const Point3D &p1, const Point3D &p2 );
    static Vector3D NormalBy3Points( const Point3D &p1, const Point3D &p2, const Point3D &p3);
    const Vector3D ToVector3D( bool normalize = true ) const;
};


struct Spectrum
{
public:
    Spectrum();
    Spectrum( Coordinate rgb );
    Spectrum( Coordinate _r, Coordinate _g, Coordinate _b );

    const Spectrum operator+=( const Spectrum &right );
    const Spectrum operator*=( const Spectrum &right );
    const Spectrum operator/=( const Spectrum &right );
    Spectrum operator/( const Coordinate right ) const;
    const Spectrum operator*( const Coordinate right );
    Spectrum operator+( const Spectrum &right ) const ;
    Spectrum operator-( const Spectrum &right ) const ;
    //Spectrum operator+( Spectrum &right );
    Spectrum operator*( const Spectrum &right );

    Coordinate MaxValue();
    Coordinate Sum();

    Coordinate getColorR();
    Coordinate getColorG();
    Coordinate getColorB();

private:
        Coordinate r;
        Coordinate g;
        Coordinate b;
};

class Ray
{
public:

    Point3D from;
    Point3D to;
    Vector3D direction;

    Ray( Point3D _from, Point3D _to );
    Ray( Point3D _from, Vector3D _dir );
};


#endif // TYPES_H
