#include <memory>

#include "draw_manager.h"

void DrawManager::drawScene(std::shared_ptr<Scene> scene)
{
    for (auto iter = scene->begin(); iter != scene->end(); ++iter)
        (*iter)->accept(*_visitor);
}
