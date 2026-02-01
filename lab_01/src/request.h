#ifndef REQUEST_H
#define REQUEST_H

#include "errors.h"

enum action_t
{
    LOAD,
    MOVE,
    SCALE,
    TURN,
    DRAW,
    QUIT
};

struct transform_t
{
    double x, y, z;
};

struct request_t
{
    action_t action;
    const char *filename;
    transform_t transform;
};

err_t handle_request(const request_t &request);

#endif
