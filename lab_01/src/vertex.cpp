#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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

void move_vertex(vertex_t &vertex, const transform_t &transform)
{
    vertex.x += transform.x;
    vertex.y += transform.y;
    vertex.z += transform.z;
}

err_t move_vertexes(vertexes_arr_t &vertexes, const transform_t &transform)
{
    if (!vertexes.data || !vertexes.len)
        return ERR_NO_DATA;

    for (size_t i = 0; i < vertexes.len; i++)
        move_vertex(vertexes.data[i], transform);

    return ERR_OK;
}

void scale_vertex(vertex_t &vertex, const vertex_t &centre, const transform_t &scale)
{
    vertex.x = centre.x + scale.x * (vertex.x - centre.x);
    vertex.y = centre.y + scale.y * (vertex.y - centre.y);
    vertex.z = centre.z + scale.z * (vertex.z - centre.z);
}

err_t scale_vertexes(vertexes_arr_t &vertexes, const vertex_t &centre, const transform_t &scale)
{
    if (!vertexes.data || !vertexes.len)
        return ERR_NO_DATA;

    for (size_t i = 0; i < vertexes.len; i++)
        scale_vertex(vertexes.data[i], centre, scale);

    return ERR_OK;
}

double to_radians(const double angle)
{
    return M_PI / 180 * angle;
}

void xturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle);
    double cos_a = cos(rad_angle);
    double sin_a = sin(rad_angle);
    double tmp_y = vertex.y;

    vertex.y = vertex.y * cos_a - vertex.z * sin_a;
    vertex.z = tmp_y * sin_a + vertex.z * cos_a;
}

void yturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle);
    double cos_a = cos(rad_angle);
    double sin_a = sin(rad_angle);
    double tmp_x = vertex.x;

    vertex.x = vertex.x * cos_a - vertex.z * sin_a;
    vertex.z = tmp_x * sin_a + vertex.z * cos_a;
}

void zturn_vertex(vertex_t &vertex, const double angle)
{
    double rad_angle = to_radians(angle);
    double cos_a = cos(rad_angle);
    double sin_a = sin(rad_angle);
    double tmp_x = vertex.x;

    vertex.x = vertex.x * cos_a - vertex.y * sin_a;
    vertex.y = tmp_x * sin_a + vertex.y * cos_a;
}

void move_to_centre(vertex_t &vertex, const vertex_t &centre)
{
    vertex.x -= centre.x;
    vertex.y -= centre.y;
    vertex.z -= centre.z;
}

void move_back(vertex_t &vertex, const vertex_t &centre)
{
    vertex.x += centre.x;
    vertex.y += centre.y;
    vertex.z += centre.z;
}

void turn_vertex(vertex_t &vertex, const vertex_t &centre, const transform_t &turn)
{
    move_to_centre(vertex, centre);
    xturn_vertex(vertex, turn.x);
    yturn_vertex(vertex, turn.y);
    zturn_vertex(vertex, turn.z);
    move_back(vertex, centre);
}

err_t turn_vertexes(vertexes_arr_t &vertexes, const vertex_t &centre, const transform_t &turn)
{
    if (!vertexes.data || !vertexes.len)
        return ERR_NO_DATA;

    for (size_t i = 0; i < vertexes.len; i++)
        turn_vertex(vertexes.data[i], centre, turn);

    return ERR_OK;
}
