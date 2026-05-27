#ifndef SOLUTION_DRAW_H
#define SOLUTION_DRAW_H

#include <memory>

#include "base_camera.h"
#include "base_drawer.h"
#include "base_solution.h"
#include "base_visitor.h"
#include "draw_manager.h"
#include "scene.h"

class SolutionDraw : public BaseSolution
{
public:
    SolutionDraw() = default;
    SolutionDraw(std::shared_ptr<DrawManager> manager,
                 std::shared_ptr<BaseVisitor> visitor,
                 std::shared_ptr<BaseDrawer> drawer);

    void setDrawer(std::shared_ptr<BaseDrawer> drawer);
    void setVisitor(std::shared_ptr<BaseVisitor> visitor);
    void drawSceneWithCamera(std::shared_ptr<Scene> scene, std::shared_ptr<BaseCamera> camera);

private:
    std::shared_ptr<DrawManager> _manager;
    std::shared_ptr<BaseVisitor> _visitor;
    std::shared_ptr<BaseDrawer> _drawer;
};

#endif
