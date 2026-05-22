#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>

#include "base_camera.h"
#include "base_drawer.h"
#include "base_manager.h"
#include "base_visitor.h"
#include "scene.h"

class DrawManager : public BaseManager
{
public: 
    DrawManager() = default;
    ~DrawManager() override = default;

    void setVisitor(std::shared_ptr<BaseVisitor> visitor) { _visitor = visitor; };
    void drawScene(std::shared_ptr<Scene> scene);
    void drawScene(std::shared_ptr<Scene> scene,
                   std::shared_ptr<BaseVisitor> visitor,
                   std::shared_ptr<BaseDrawer> drawer,
                   std::shared_ptr<BaseCamera> camera);

private:
    std::shared_ptr<BaseVisitor> _visitor;
};

#endif
