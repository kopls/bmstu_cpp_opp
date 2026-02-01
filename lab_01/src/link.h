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
err_t read_links_arr_len(links_arr_t &links, FILE *file);
err_t allocate_links_arr(links_arr_t &links);
err_t read_link(link_t &link, FILE *file);
err_t read_links_data(links_arr_t &links, FILE *file);
err_t read_links(links_arr_t &links, FILE *file);
err_t check_link(const link_t &link, const size_t max_vertex_num);
err_t check_links(const links_arr_t &links, const size_t max_vertex_num);

#endif
