#include "draw_manager.h"

void DrawManager::setVisitor(std::shared_ptr<BaseVisitor> visitor)
{
    _visitor = visitor;
}
