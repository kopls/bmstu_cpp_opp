#ifndef SCENE_H
#define SCENE_H

#include <cstddef>
#include <memory>
#include <vector>

#include "object.h"

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void addObject(const std::shared_ptr<Object> &object);
    void deleteObject(Iterator &iter);

    Iterator getObject(const std::size_t id);

    Iterator begin();
    Iterator end();

private:
    std::vector<std::shared_ptr<Object>> _objects;
};

#endif
