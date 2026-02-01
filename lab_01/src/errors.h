#ifndef ERRORS_H
#define ERRORS_H

enum err_t
{
    ERR_OK,
    ERR_TRANSFORM_READ,
    ERR_READ_VERTEX,
    ERR_MEMORY_VERTEXES_ARR,
    ERR_READ_VERTEXES_LEN,
    ERR_VALUE_VERTEXES_LEN,
    ERR_READ_LINKS_LEN,
    ERR_VALUE_LINKS_LEN,
    ERR_MEMORY_LINKS_ARR,
    ERR_BAD_LINK
};

void handle_error(const err_t rc);

#endif
