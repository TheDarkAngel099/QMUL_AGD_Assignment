#include "../../include/utils/Rectangle.h"

bool Rectangle::inside(float x, float y) const
{
    if (x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y) 
        return true;

    return false;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    if (inside(rect.topLeft.x, rect.topLeft.y) || inside(rect.bottomRight.x, rect.bottomRight.y) || inside(rect.topLeft.x, rect.bottomRight.y) || inside(rect.bottomRight.x, rect.topLeft.y))
        return true;

    return false;
}

