#include "link.h"

void links_init(links_arr_t &links);
static err_t read_links_arr_len(links_arr_t &links, FILE *file);
static err_t allocate_links_arr(links_arr_t &links);
static err_t read_links_data(links_arr_t &links, FILE *file);
static err_t read_link(link_t &link, FILE *file);
static err_t check_link(const link_t &link, const size_t max_vertex_num);
static err_t check_vertex(const size_t vertex, const size_t max_vertex);
static bool more_than_max(const size_t vertex, const size_t max_vertex);

void destroy_links_arr(links_arr_t &links)
{
    free(links.data);
    links_init(links);
}

void links_init(links_arr_t &links)
{
    links.data = NULL;
    links.len = 0;
}

err_t read_links(links_arr_t &links, FILE *file)
{
    if (!file)
        return ERR_OPEN_FILE;

    err_t rc = read_links_arr_len(links, file);
    if (rc == ERR_OK)
    {
        rc = allocate_links_arr(links);
        if (rc == ERR_OK) 
            rc = read_links_data(links, file);

    }

    if (rc != ERR_OK)
        destroy_links_arr(links);

    return rc;
}

static err_t read_links_arr_len(links_arr_t &links, FILE *file)
{
    if (!file)
        return ERR_OPEN_FILE;

    err_t rc = ERR_OK;
    if (fscanf(file, "%lu", &links.len) != 1)
        rc = ERR_READ_LINKS_LEN;

    if (rc == ERR_OK)
        if (links.len == 0)
            return ERR_VALUE_LINKS_LEN;

    return ERR_OK;
}

static err_t allocate_links_arr(links_arr_t &links)
{
    links.data = (link_t *)malloc(links.len * sizeof(link_t));
    if (!links.data)
        return ERR_MEMORY_LINKS_ARR;

    return ERR_OK;
}

static err_t read_links_data(links_arr_t &links, FILE *file)
{
    if (!file)
        return ERR_OPEN_FILE;
    
    if (!links.data)
        return ERR_NULL_POINTER;

    err_t rc = ERR_OK;
    for (size_t i = 0; i < links.len && rc == ERR_OK; i++)
        rc = read_link(links.data[i], file);

    return rc;
}

static err_t read_link(link_t &link, FILE *file)
{
    if (!file)
        return ERR_OPEN_FILE;

    if (fscanf(file, "%lu%lu", &link.vertex1, &link.vertex2) != 2)
        return ERR_READ_LINK;

    return ERR_OK;
}

err_t check_links(const links_arr_t &links, const size_t max_vertex_num)
{
    if (!links.data)
        return ERR_NULL_POINTER;

    err_t rc = ERR_OK;   
    for (size_t i = 0; i < links.len && rc == ERR_OK; i++)
        rc = check_link(links.data[i], max_vertex_num);

    return rc;
}

static err_t check_link(const link_t &link, const size_t max_vertex_num)
{
    if (check_vertex(link.vertex1, max_vertex_num) != ERR_OK ||
        check_vertex(link.vertex2, max_vertex_num) != ERR_OK) 
        return ERR_BAD_LINK;

    return ERR_OK;
}

static err_t check_vertex(const size_t vertex, const size_t max_vertex)
{
    err_t rc = ERR_OK;
    if (more_than_max(vertex, max_vertex))
        rc = ERR_MAX_VERTEX;

    return rc;
}

static bool more_than_max(const size_t vertex, const size_t max_vertex)
{
    if (vertex > max_vertex)   
        return true;
    return false;
}
// те же ошибки что в поинтс, статики сделать, от большего к меньшему функции сверху вниз
