#ifndef SOLUTION_SCENE_H
#define SOLUTION_SCENE_H

#include <cstddef>
#include <memory>
#include <vector>

#include "base_solution.h"
#include "base_camera.h"
#include "object.h"
#include "scene.h"
#include "scene_manager.h"
#include "scene_memento.h"

class SolutionScene : public BaseSolution
{
public:
    SolutionScene() = default;
    explicit SolutionScene(std::shared_ptr<SceneManager> manager);

    void setScene(std::shared_ptr<Scene> scene);
    std::shared_ptr<Scene> getScene() const;

    void addObjectWithId(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id);
    void deleteObject(std::size_t id);
    void collectVisibleObjectsToComposite();
    void splitCompositesToObjects();

    void setCamera(std::size_t id);
    std::shared_ptr<BaseCamera> getCamera() const;
    std::size_t getCameraId() const;
    bool hasCamera() const;
    std::vector<std::size_t> getCameraIds() const;

    SceneMemento createMemento() const;
    void restoreMemento(const SceneMemento &memento);

private:
    std::shared_ptr<SceneManager> _manager;
};

#endif
