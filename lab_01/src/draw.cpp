#include "draw.h"

void project_to_centre(vertex_t &vertex, const double width, const double height)
{
    vertex.x += width / 2;
    vertex.y += height / 2;
}

void draw_line(const double x1, const double y1,
               const double x2, const double y2,
               const canvas_t &canvas)
{
    canvas.scene->addLine(x1, y1, x2, y2);
}

void clear_canvas(const canvas_t &canvas)
{
    canvas.scene->clear();
}

void draw_link(const link_t &link, const vertexes_arr_t &vertexes, const canvas_t &canvas)
{
    vertex_t vertex1 = vertexes.data[link.vertex1 - 1];
    vertex_t vertex2 = vertexes.data[link.vertex2 - 1];

    project_to_centre(vertex1, canvas.width, canvas.height);
    project_to_centre(vertex2, canvas.width, canvas.height);

    draw_line(vertex1.x, vertex1.y, vertex2.x, vertex2.y, canvas);
}

err_t draw_links(const links_arr_t &links, const vertexes_arr_t &vertexes, const canvas_t &canvas)
{
    if (!links.data || !links.len || !vertexes.data || !vertexes.len)
        return ERR_DRAW_DATA;

    for (size_t i = 0; i < links.len; i++)
        draw_link(links.data[i], vertexes, canvas);

    return ERR_OK;
}

err_t draw_figure(const figure_t &figure, const canvas_t &canvas)
{
    clear_canvas(canvas);
    err_t rc = draw_links(figure.links, figure.vertexes, canvas);
    return rc;
}
