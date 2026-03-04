#ifndef DRAW_H
#define DRAW_H

#include "link.h"
#include "figure.h"
#include "canvas.h"
#include "errors.h"

err_t draw_figure(const figure_t &figure, const canvas_t &canvas);

#endif
