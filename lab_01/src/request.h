#ifndef REQUEST_H
#define REQUEST_H

enum action_t
{
    LOAD;
    MOVE;
    SCALE;
    TURN;
    DRAW;
    QUIT;
};

struct transform_data_t
{
    double dx, dy, dz;
};

struct request_t
{
    action_t action;
    const char *filename;
    transform_data_t transform;
};

err_t handle_request(request_t req);

#endif
