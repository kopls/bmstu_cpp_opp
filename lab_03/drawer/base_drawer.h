#ifndef BASE_DRAWER_H
#define BASE_DRAWER_H

#include "point.h"

class BaseDrawer
{
public:
    virtual ~BaseDrawer() = default;

    virtual void drawLine(const Point &p1, const Point &p2) = 0;
    virtual void clearScene() = 0;
};

#endif
