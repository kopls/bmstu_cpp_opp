#include "solution_load.h"

#include <stdexcept>

SolutionLoad::SolutionLoad(std::shared_ptr<LoadManager> manager)
    : _manager(manager)
{
}

std::shared_ptr<Scene> SolutionLoad::loadScene(const std::string &fileName)
{
    if (!_manager)
        throw std::logic_error("SolutionLoad: manager is not set");

    return _manager->loadScene(fileName);
}

void SolutionLoad::loadObjectToScene(const std::shared_ptr<Scene> &scene,
                                     const std::string &fileName,
                                     const std::shared_ptr<std::size_t> &id)
{
    if (!_manager)
        throw std::logic_error("SolutionLoad: manager is not set");

    _manager->loadObjectToScene(scene, fileName, id);
}

void SolutionLoad::loadModelToScene(const std::shared_ptr<Scene> &scene,
                                    const std::string &fileName,
                                    ModelFileFormat format,
                                    ModelRepresentation representation,
                                    const std::shared_ptr<std::size_t> &id)
{
    if (!_manager)
        throw std::logic_error("SolutionLoad: manager is not set");

    _manager->loadModelToScene(scene, fileName, format, representation, id);
}
