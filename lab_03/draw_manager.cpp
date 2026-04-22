#include <memory>

#include "draw_manager.h"

void DrawManager::setVisitor(std::shared_ptr<BaseVisitor> visitor)
{
    _visitor = visitor;
}

void DrawManager::drawScene(std::shared_ptr<Scene> scene)
{
    for (auto &elem : *scene)
        elem->accept(*_visitor);
}
