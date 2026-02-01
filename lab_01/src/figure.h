#ifndef FIGURE_H
#define FIGURE_H

#include "request.h"
#include "vertex.h"
#include "link.h"

struct figure_t
{
    vertex_t centre;
    vertexes_arr_t vertexes;
    links_arr_t links;
};

figure_t &figure_init(void);
void destroy_figure(figure_t &figure);
err_t read_figure(figure_t &figure, FILE *file);
err_t load_figure(figure_t &figure, const char *filename);
err_t move_figure(figure_t &figure, const transform_t &transform);
err_t scale_figure(figure_t &figure, const transform_t &transform);
err_t turn_figure(figure_t &figure, const transform_t &transform);

#endif
