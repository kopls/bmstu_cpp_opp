#include "request.h"
#include "stdio.h"

err_t handle_request(const request_t &request)
{
    err_t rc = ERR_OK;
    static figure_t figure = figure_init();

    switch (request.action)
    {
    case LOAD:
        printf("Action: LOAD file %s\n", request.filename);
        rc = load_figure(figure, request.filename);
        break;
    case MOVE:
        printf("Action: MOVE by %f %f %f\n", request.transform.x, request.transform.y, request.transform.z);
        break;
    case SCALE:
        printf("Action: SCALE by %f %f %f\n", request.transform.x, request.transform.y, request.transform.z);
        break;
    case TURN:
        printf("Action: TURN  by %f %f %f\n", request.transform.x, request.transform.y, request.transform.z);
        break;
    case DRAW:
        printf("Action: DRAW\n");
        rc = draw_figure(figure, request.canvas);
        break;
    case QUIT:
        printf("Action: QUIT\n");
        break;
    default:
        printf("Unknown action\n");

    }

    return rc;
};
