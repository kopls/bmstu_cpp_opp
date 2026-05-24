#ifndef SCENE_H
#define SCENE_H

#include <cstddef>
#include <memory>
#include <vector>

#include "base_camera.h"
#include "object.h"

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    std::shared_ptr<Scene> clone() const;

    void addObject(const std::shared_ptr<Object> &object);
    void addObject(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id);
    void addObjectWithId(const std::shared_ptr<Object> &object, const std::shared_ptr<std::size_t> &id);

    void deleteObject(Iterator &iter);
    void deleteObject(std::size_t id);

    Iterator getObject(const std::size_t id);
    std::shared_ptr<BaseCamera> getCamera(std::size_t id);
    std::vector<std::size_t> getCameraIds() const;
    std::size_t visibleObjectCount() const;

    void collectVisibleObjectsToComposite();
    void splitCompositesToObjects();

    Iterator begin();
    Iterator end();

private:
    void collectCameraIds(const std::shared_ptr<Object> &object, std::vector<std::size_t> &ids) const;
    std::shared_ptr<BaseCamera> getCamera(const std::shared_ptr<Object> &object, std::size_t id);

    std::vector<std::shared_ptr<Object>> _objects;
};

#endif
