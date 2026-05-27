#ifndef SOLUTION_TRANSFORM_CREATOR_H
#define SOLUTION_TRANSFORM_CREATOR_H

#include <memory>

#include "base_solution_creator.h"
#include "solution_transform.h"
#include "transform_manager_creator.h"

class SolutionTransformCreator : public BaseSolutionCreator<SolutionTransform>
{
protected:
    std::shared_ptr<SolutionTransform> create() override
    {
        TransformManagerCreator creator;
        return std::make_shared<SolutionTransform>(creator.getManager());
    }
};

#endif
