#ifndef SOLUTION_PACK_H
#define SOLUTION_PACK_H

#include <memory>

#include "solution_draw.h"
#include "solution_load.h"
#include "solution_scene.h"
#include "solution_transform.h"

struct SolutionPack
{
    std::shared_ptr<SolutionScene> scene;
    std::shared_ptr<SolutionTransform> transform;
    std::shared_ptr<SolutionDraw> draw;
    std::shared_ptr<SolutionLoad> load;
};

#endif
