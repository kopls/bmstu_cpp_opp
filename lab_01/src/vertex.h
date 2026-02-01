#ifndef VERTEX_H
#define VERTEX_H


#include "request.h"
#include "errors.h"

struct vertex_t
{
    double x;
    double y;
    double z;
};

struct vertexes_arr_t
{
    vertex_t *data;
    size_t len;
};

void vertex_init(vertex_t &v);
void vertexes_init(vertexes_arr_t &v);
void destroy_vertexes_arr(vertexes_arr_t &vertexes);
size_t get_vertexes_num(const vertexes_arr_t &vertexes);
err_t read_vertex(vertex_t &vertex, FILE *file);
err_t read_vertexes_len(vertexes_arr_t &vertexes, FILE *file);
err_t read_vertexes_data(vertexes_arr_t &vertexes, FILE *file);
err_t allocate_vertexes_arr(vertexes_arr_t &vertexes);
err_t read_vertexes(vertexes_arr_t &vertexes, FILE *file);

void move_vertex(vertex_t &vertex, const transform_t &transform);
err_t move_vertexes(vertexes_arr_t &vertexes, const transform_t &transform);

void scale_vertex(vertex_t &vertex, const vertex_t &centre, const transform_t &scale);
err_t scale_vertexes(vertexes_arr_t &vertexes, const vertex_t &centre, const transform_t &scale);

double to_radians(const double angle);
void xturn_vertex(vertex_t &vertex, const double angle);
void yturn_vertex(vertex_t &vertex, const double angle);
void zturn_vertex(vertex_t &vertex, const double angle);
void move_to_centre(vertex_t &vertex, const vertex_t &centre);
void move_back(vertex_t &vertex, const vertex_t &centre);
void turn_vertex(vertex_t &vertex, const vertex_t &centre, const transform_t &turn);
err_t turn_vertexes(vertexes_arr_t &vertexes, const vertex_t &centre, const transform_t &turn);

#endif
