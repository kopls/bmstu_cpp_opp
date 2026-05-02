#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include "draw_manager.h"
#include "scene_manager.h"
#include "transform_manager.h"
#include "drawer_visitor.h"

class BaseCommand
{
public:
    BaseCommand() = default;
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;

    void setManagers(std::shared_ptr<DrawManager> drawManager, std::shared_ptr<SceneManager> sceneManager, std::shared_ptr<TransformManager> transformManager,
                     std::shared_ptr<DrawerVisitor> visitor); 

protected:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transformManager;
    std::shared_ptr<DrawerVisitor> _visitor;
};

#endif
