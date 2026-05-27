#ifndef SOLUTION_SCENE_CREATOR_H
#define SOLUTION_SCENE_CREATOR_H

#include <memory>

#include "base_solution_creator.h"
#include "scene_manager_creator.h"
#include "solution_scene.h"

class SolutionSceneCreator : public BaseSolutionCreator<SolutionScene>
{
protected:
    std::shared_ptr<SolutionScene> create() override
    {
        SceneManagerCreator creator;
        auto solution = std::make_shared<SolutionScene>(creator.getManager());

        solution->setScene(std::make_shared<Scene>());

        return solution;
    }
};

#endif
