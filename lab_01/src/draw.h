#ifndef DRAW_H
#define DRAW_H

#include <stdlib.h>
#include "errors.h"
#include "canvas.h"
#include "figure.h"

err_t draw_figure(const figure_t &figure, const canvas_t &canvas);

#endif
