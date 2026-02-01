#ifndef CANVAS
#define CANVAS

#include <QGraphicsScene>

struct canvas_t
{
    QGraphicsScene *scene;
    double width;
    double height;
};

void draw_line(const double x1, const double y1, 
               const double x2, const double y2,
               const canvas_t &canvas);

void clear_canvas(const canvas_t &canvas);

#endif
