#ifndef LINK_H
#define LINK_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

struct link_t
{
    size_t vertex1;
    size_t vertex2;
};

struct links_arr_t
{
    link_t *data;
    size_t len;
};

void links_init(links_arr_t &links);
void destroy_links_arr(links_arr_t &links);
err_t read_links(links_arr_t &links, FILE *file);
err_t check_links(const links_arr_t &links, const size_t max_vertex_num);

#endif
