#include "ClickableObject.h"

namespace game 
{
    bool ClickableObject::PointInPolygon(Point point) {
        int i, j, nvert = ClickPoligon.size();
        bool c = false;
        for (i = 0, j = nvert - 1; i < nvert; j = i++) {
            if (((ClickPoligon[i].y >= point.y) != (ClickPoligon[j].y >= point.y)) &&
                (point.x <= (ClickPoligon[j].x - ClickPoligon[i].x) * 
                (point.y - ClickPoligon[i].y) / (ClickPoligon[j].y - ClickPoligon[i].y) + ClickPoligon[i].x)
                )
                c = !c;
        }
        return c;
    }

}
