#include "figure.h"

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
    destroy_vertex_arr(figure.vertexes);
    destroy_links_arr(figure.links);
}

err_t read_figure(figure_t &figure, FILE *file)
{
    figure = figure_init();

    err_t rc = read_vertex(figure.centre, file);
    if (rc) return rc;

    rc = read_vertexes(figure.vertexes, file);
    if (rc) return rc;

    rc = read_links(figure.links, file);
    if (rc)
    {
        destroy_vertexes_arr(figure.vertexes);
        return rc;
    }

    rc = check_links(figure.links, get_vertex_num(figure.vertexes)); 
    if (rc)
        destroy_figure(figure);

    return rc;
}

err_t load_figure(figure_t &figure, const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (!f)
        return ERR_OPEN_FILE;

    figure_t tmp_figure;

    err_t rc = read_figure(tmp_figure, f);

    fclose(f);

    if (!rc)
    {
        destroy_figure(figure);
        figure = tmp_figure;
    }

    return rc;
}
















