#include "link.h"

void links_init(links_arr_t &links)
{
    links.data = NULL;
    links.len = 0;
}

void destroy_links_arr(links_arr_t &links)
{
    free(links.data);
    links_init(links);
}

err_t read_links_arr_len(links_arr_t &links, FILE *file)
{
    if (fscanf(file, "%lu", &links.len) != 1)
        return ERR_READ_LINKS_LEN;

    if (links.len == 0)
        return ERR_VALUE_LINKS_LEN;

    return ERR_OK;
}

err_t allocate_links_arr(links_arr_t &links)
{
    links.data = (link_t *)malloc(links.len * sizeof(link_t));
    if (!links_data)
        return ERR_MEMORY_LINKS_ARR;

    return ERR_OK;
}

err_t read_link(link_t &link, FILE *file)
{
    if (fscanf(file, "%lu%lu", &link.vertex1, &link.vertex2) != 2)
        return ERR_READ_LINK;

    return ERR_OK;
}

err_t read_links_data(links_arr_t &links, FILE *file)
{
    err_t rc = OK;
    for (int i = 0; i < links.len; i++)
        rc = read_link(links.data[i], file);

    return rc;
}

err_t read_links(links_arr_t &links, FILE *file)
{
    err_t rc = read_links_arr_len(links, file);

    if (!rc)
        rc = allocate_links_arr(links);

    if (!rc) 
        rc = read_links_data(links, file);

    if (rc)
        destroy_links_arr(links);

    return rc;
}

err_t check_link(const link_t &link, int max_vertex_num)
{
    if (!link.vertex1 || link.vertex1 > max_vertex_num
        || !link.vertex2 || link.vertex2 > max_vertex_num)
        return ERR_BAD_LINK;

    return ERR_OK;
}

err_t check_links(const links_arr_t &links, const int max_vertex_num)
{
    err_t rc = ERR_OK;   
    for (int i = 0; i < links.len && !rc; i++)
        rc = check_link(links.data[i], max_vertex_num);

    return rc;
}






