#ifndef DRAW_H
#define DRAW_H

#include <QGraphicsScene>

#include "figure.h"

struct canvas_t
{
    QGraphicsScene *scene;
    double width;
    double height;
};

void project_to_centre(vertex_t &vertex, const double width, const double height);

void draw_line(const double x1, const double y1, 
               const double x2, const double y2,
               const canvas_t &canvas);
void clear_canvas(const canvas_t &canvas);
err_t draw_figure(const figure_t &figure, const canvas_t &canvas);

#endif
