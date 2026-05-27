#ifndef SOLUTION_LOAD_H
#define SOLUTION_LOAD_H

#include <cstddef>
#include <memory>
#include <string>

#include "base_solution.h"
#include "load_manager.h"
#include "model_load_options.h"
#include "scene.h"

class SolutionLoad : public BaseSolution
{
public:
    SolutionLoad() = default;
    explicit SolutionLoad(std::shared_ptr<LoadManager> manager);

    std::shared_ptr<Scene> loadScene(const std::string &fileName);
    void loadObjectToScene(const std::shared_ptr<Scene> &scene,
                           const std::string &fileName,
                           const std::shared_ptr<std::size_t> &id);
    void loadModelToScene(const std::shared_ptr<Scene> &scene,
                          const std::string &fileName,
                          ModelFileFormat format,
                          ModelRepresentation representation,
                          const std::shared_ptr<std::size_t> &id);

private:
    std::shared_ptr<LoadManager> _manager;
};

#endif
