#include "request.h"

err_t handle_request(const request_t &request)
{
    err_t rc = ERR_OK;
    static figure_t figure = figure_init();

    switch (request.action)
    {
    case LOAD:
        rc = load_figure(figure, request.filename);
        break;
    case MOVE:
        rc = move_figure(figure, request.transform);
        break;
    case SCALE:
        rc = scale_figure(figure, request.transform);
        break;
    case TURN:
        rc = turn_figure(figure, request.transform);
        break;
    case DRAW:
        rc = draw_figure(figure, request.canvas);
        break;
    case QUIT:
        break;
    default:
        rc = ERR_UNKNOWN;
    }

    return rc;
};
