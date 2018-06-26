#include "types.h"

#include <math.h>


Vector3D::Vector3D() : X(0), Y(0), Z(1)
{
}


Vector3D::Vector3D(Coordinate x, Coordinate y, Coordinate z, bool normalize): X(x), Y(y), Z(z)
{
    if ( normalize )
        this->Normalize();
}

Vector3D::Vector3D(const Point3D &from, const Point3D &to, bool normalize )
{
    double x = (double)to.X - (double)from.X;
    double y = (double)to.Y - (double)from.Y;
    double z = (double)to.Z - (double)from.Z;

    if ( normalize )
    {
        double n = (double)sqrt( x*x + y*y + z*z );
        x = x / n;
        y = y / n;
        z = z / n;
    }

    this->X = x;
    this->Y = y;
    this->Z = z;

    /*
    this->X = to.X - from.X;
    this->Y = to.Y - from.Y;
    this->Z = to.Z - from.Z;
    if ( normalize )
        this->Normalize();
    */
}

Vector3D::Vector3D(const float theta, const float phi)
{
    this->Z = sin(theta);
    double rcoselev = cos(theta);
    this->X = rcoselev * cos(phi);
    this->Y = rcoselev * sin(phi);

    this->Normalize();

}

const Vector3D Vector3D::operator*(const Coordinate &right) const
{
    return Vector3D( this->X * right, this->Y * right, this->Z * right );
}

const Vector3D Vector3D::operator/(const Coordinate &right) const
{
    return Vector3D( this->X / right, this->Y / right, this->Z / right );
}

const Vector3D Vector3D::operator*(const Vector3D &right) const
{
    return Vector3D( this->Y * right.Z - this->Z * right.Y,
                     this->Z * right.X - this->X * right.Z,
                     this->X * right.Y - this->Y * right.X );
}

const Vector3D Vector3D::operator+(const Vector3D &right) const
{
    return Vector3D( this->X + right.X, this->Y + right.Y, this->Z + right.Z );
}

const Vector3D Vector3D::operator-(const Vector3D &right) const
{
    return Vector3D( this->X - right.X, this->Y - right.Y, this->Z - right.Z );
}

const Vector3D Vector3D::operator+=(const Vector3D &right)
{
    X += right.X;
    Y += right.Y;
    Z += right.Z;

    return *this;
}

const Vector3D Vector3D::Reflect(const Vector3D &normal, bool normalize)
{
    Vector3D result = Vector3D::Reflect( *this, normal );

    if ( normalize )
        result.Normalize();

    return result;
}


const Point3D Vector3D::ToPoint3D() const
{
    return Point3D (this->X, this->Y, this->Z );
}

Coordinate Vector3D::Dot(const Vector3D &v1, const Vector3D &v2)
{
    return v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
}

Vector3D Vector3D::Reflect(const Vector3D &fall, const Vector3D &normal)
{
    return fall - normal * Dot( fall, normal ) * 2;
}

void Vector3D::Normalize()
{
    Coordinate n = (Coordinate)sqrtf( this->X * this->X + this->Y * this->Y + this->Z * this->Z );
    this->X /= n;
    this->Y /= n;
    this->Z /= n;
}


Point3D::Point3D()
{
}

Point3D::Point3D(Coordinate x, Coordinate y, Coordinate z) : X(x), Y(y), Z(z)
{

}

Coordinate Point3D::Length() const
{
    return sqrtf( X * X + Y * Y + Z * Z );
}

Coordinate Point3D::Length2() const
{
    return X * X + Y * Y + Z * Z;
}

const Point3D Point3D::operator*(const Point3D &right) const
{
    return Point3D( this->Y * right.Z - this->Z * right.Y,
                    this->Z * right.X - this->X * right.Z,
                    this->X * right.Y - this->Y * right.X );
}

const Point3D Point3D::operator/(const Coordinate &right) const
{
    return Point3D( this->X / right, this->Y / right, this->Z / right );
}

const Point3D Point3D::operator+(const Vector3D &right) const
{
    return Point3D( this->X + right.X, this->Y + right.Y, this->Z + right.Z );
}

const Point3D Point3D::operator+(const Point3D &right) const
{
    return Point3D( this->X + right.X, this->Y + right.Y, this->Z + right.Z );
}

const Point3D Point3D::operator-(const Point3D &right) const
{
    return Point3D( this->X - right.X, this->Y - right.Y, this->Z - right.Z );
}

Coordinate Point3D::Dot(const Point3D &p1, const Point3D &p2)
{
    return p1.X * p2.X + p1.Y * p2.Y + p1.Z * p2.Z;
}

Coordinate Point3D::Length(const Point3D &p1, const Point3D &p2)
{
    return sqrtf( Point3D::LengthSquared( p1, p2 ) );
}

Coordinate Point3D::LengthSquared(const Point3D &p1, const Point3D &p2)
{
    float x = p2.X - p1.X;
    float y = p2.Y - p1.Y;
    float z = p2.Z - p1.Z;

    return x * x + y * y + z * z;
}

Vector3D Point3D::NormalBy3Points(const Point3D &p1, const Point3D &p2, const Point3D &p3)
{
    double v1x = (double)p2.X - p1.X;
    double v1y = (double)p2.Y - p1.Y;
    double v1z = (double)p2.Z - p1.Z;

    double v2x = (double)p3.X - p1.X;
    double v2y = (double)p3.Y - p1.Y;
    double v2z = (double)p3.Z - p1.Z;

    double vx = v1y * v2z - v1z * v2y;
    double vy = v1z * v2x - v1x * v2z;
    double vz = v1x * v2y - v1y * v2x;

    double norm = sqrt( vx * vx + vy * vy + vz * vz );

    return Vector3D( vx / norm, vy / norm, vz / norm );
}

const Vector3D Point3D::ToVector3D( bool normalize ) const
{
    return Vector3D( this->X, this->Y, this->Z, normalize );
}


Spectrum::Spectrum()
{
}

Spectrum::Spectrum(Coordinate rgb) : r(rgb), g(rgb), b(rgb)
{

}

Spectrum::Spectrum(Coordinate _r, Coordinate _g, Coordinate _b) : r(_r), g(_g), b(_b)
{

}


const Spectrum Spectrum::operator+=(const Spectrum &right)
{
    r += right.r;
    g += right.g;
    b += right.b;

    return *this;
}

const Spectrum Spectrum::operator*=(const Spectrum &right)
{
    r *= right.r;
    g *= right.g;
    b *= right.b;

    return *this;
}

const Spectrum Spectrum::operator/=(const Spectrum &right)
{
    r /= right.r;
    g /= right.g;
    b /= right.b;

    return *this;
}

Spectrum Spectrum::operator/(const Coordinate right) const
{
    return Spectrum( this->r / right, this->g / right, this->b / right );
}

const Spectrum Spectrum::operator*(const Coordinate right)
{
    return Spectrum( this->r * right, this->g * right, this->b * right );
}

Spectrum Spectrum::operator+(const Spectrum &right) const
{
    return Spectrum( this->r + right.r, this->g + right.g, this->b + right.b );
}

Spectrum Spectrum::operator-(const Spectrum &right) const
{
    return Spectrum( this->r - right.r, this->g - right.g, this->b - right.b );
}

Spectrum Spectrum::operator*(const Spectrum &right)
{
    return Spectrum( this->r * right.r, this->g * right.g, this->b * right.b );
}

Coordinate Spectrum::MaxValue()
{
    if ( r > g && r > b )
        return r;
    else if ( g > r && g > b )
        return g;
    else
        return b;
}

Coordinate Spectrum::Sum()
{
    return r + g + b;
}

Coordinate Spectrum::getColorR()
{
    return this->r;
}

Coordinate Spectrum::getColorG()
{
    return this->g;
}

Coordinate Spectrum::getColorB()
{
    return this->b;
}


Ray::Ray(Point3D _from, Point3D _to) : from(_from), to(_to), direction( Vector3D(from, to, true) )
{

}

Ray::Ray(Point3D _from, Vector3D _dir) : from(_from), direction( _dir ), to( _from + _dir.ToPoint3D() )
{

}

