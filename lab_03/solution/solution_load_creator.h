#ifndef SOLUTION_LOAD_CREATOR_H
#define SOLUTION_LOAD_CREATOR_H

#include <memory>

#include "base_solution_creator.h"
#include "load_manager_creator.h"
#include "solution_load.h"

class SolutionLoadCreator : public BaseSolutionCreator<SolutionLoad>
{
protected:
    std::shared_ptr<SolutionLoad> create() override
    {
        LoadManagerCreator creator;
        return std::make_shared<SolutionLoad>(creator.getManager());
    }
};

#endif
