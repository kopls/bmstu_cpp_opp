#ifndef POINT_H
#define POINT_H

#include <cstddef>

class Point
{
public:
    Point() = default;
    ~Point() = default;

    Point(const double x, const double y, const double z);
    Point(const Point &point) = default;

   double getX() const; 
   double getY() const; 
   double getZ() const; 
   double getCenter() const; 

    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);

private:
    double _x;
    double _y;
    double _z;
};

#endif
