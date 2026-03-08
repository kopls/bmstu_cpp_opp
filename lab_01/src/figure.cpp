#include "figure.h"

static err_t read_figure(figure_t &figure, FILE *file);
static err_t check_figure(figure_t &figure);

figure_t &figure_init(void)
{
    static figure_t tmp_figure;

    vertex_init(tmp_figure.centre);
    vertexes_init(tmp_figure.vertexes);
    links_init(tmp_figure.links);

    return tmp_figure;
}

void destroy_figure(figure_t &figure)
{
    vertex_init(figure.centre);
    destroy_vertexes_arr(figure.vertexes);
    destroy_links_arr(figure.links);
}

err_t load_figure(figure_t &figure, const char *filename)
{
    if (!filename)
        return ERR_NULL_POINTER;

    FILE *f = fopen(filename, "r");
    if (!f)
        return ERR_OPEN_FILE;

    figure_t tmp_figure;

    err_t rc = read_figure(tmp_figure, f);

    if (rc == ERR_OK)
        rc = check_figure(tmp_figure);

    fclose(f);

    if (!rc)
    {
        destroy_figure(figure);
        figure = tmp_figure;
    }
    else
    {
        destroy_figure(tmp_figure);
    }

    return rc;
}

static err_t read_figure(figure_t &figure, FILE *file)
{
    if (!file)
        return ERR_OPEN_FILE;
        
    figure = figure_init();

    err_t rc = read_vertex(figure.centre, file);
    if (rc == ERR_OK)
    {
        rc = read_vertexes(figure.vertexes, file);
        if (rc == ERR_OK)
            rc = read_links(figure.links, file);
    }

    if (rc != ERR_OK)
        destroy_figure(figure);

    return rc;
}

static err_t check_figure(figure_t &figure)
{
    err_t rc = check_links(figure.links, get_vertexes_num(figure.vertexes));

    return rc;
}

err_t move_figure(figure_t &figure, const transform_t &transform)
{
    move_vertex(figure.centre, transform);
    err_t rc = move_vertexes(figure.vertexes, transform);
    return rc;
}

err_t scale_figure(figure_t &figure, const transform_t &transform)
{
    err_t rc = scale_vertexes(figure.vertexes, figure.centre, transform);
    return rc;
}

err_t turn_figure(figure_t &figure, const transform_t &transform)
{
    err_t rc = turn_vertexes(figure.vertexes, figure.centre, transform);
    return rc;
}
