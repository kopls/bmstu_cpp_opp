#ifndef VERTEX_H
#define VERTEX_H

struct vertex_t
{
    double x;
    double y;
    double z;
};

struct vertex_arr_t
{
    vertex_t *data;
    int len;
};

void vertex_init(vetrex_t &v);
void vertexes_init(vertexes_arr_t &v);
void destroy_vertex_arr(vertexes_arr_t &vertexes);
int get_vertexes_num(const vertexes_arr_t &vertexes);
err_t read_vertex(vertex_t &vertex, FILE *file);
err_t read_vertexes_len(vertexes_arr_t &vertexes, FILE *file);
err_t read_vertexes_data(vertexes_arr_t &vertexes);
err_t allocate_vertexes_arr(vertexes_arr_t &vertexes);
err_t read_vertexes(vertexes_arr_t &vertexes, FILE *file);

#endif
