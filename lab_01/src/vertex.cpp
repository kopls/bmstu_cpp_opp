#include "vertex.h"

void vertex_init(vertex_t &vertex)
{
    vertex.x = 0;
    vertex.y = 0;
    vertex.z = 0;
}

void vertexes_init(vertexes_arr_t &vertexes)
{
    vertexes.data = NULL;
    vertexes.len = 0;
}

void destroy_vertexes_arr(vertexes_arr_t &vertexes)
{
    free(vertexes.data);
    vertexes_init(vertexes);
}

size_t get_vertexes_num(const vertexes_arr_t &vertexes)
{
    return vertexes.len;
}

err_t read_vertex(vertex_t &vertex, FILE *file)
{
    if (fscanf(file, "%lf%lf%lf", &vertex.x, &vertex.y, &vertex.z) != 3)
        return ERR_READ_VERTEX;

    return ERR_OK;
}

err_t read_vertexes_len(vertexes_arr_t &vertexes, FILE *file)
{
    if (fscanf(file, "%lu", &vertexes.len) != 1)
        return ERR_READ_VERTEXES_LEN;

    if (vertexes.len == 0)
        return ERR_VALUE_VERTEXES_LEN;

    return ERR_OK;
}

err_t read_vertexes_data(vertexes_arr_t &vertexes, FILE *file)
{
    err_t rc = ERR_OK;
    for (size_t i = 0; i < vertexes.len; i++)
        rc = read_vertex(vertexes.data[i], file);

    return rc;
}

err_t allocate_vertexes_arr(vertexes_arr_t &vertexes)
{
    vertexes.data = (vertex_t *)malloc(vertexes.len * sizeof(vertex_t));
    if (!vertexes.data)
        return ERR_MEMORY_VERTEXES_ARR;

    return ERR_OK;
}

err_t read_vertexes(vertexes_arr_t &vertexes, FILE *file)
{
    err_t rc = read_vertexes_len(vertexes, file);

    if (!rc)
        rc = allocate_vertexes_arr(vertexes);

    if (!rc)
        rc = read_vertexes_data(vertexes, file);

    if (rc)
        destroy_vertexes_arr(vertexes);

    return rc;
}
