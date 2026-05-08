#include "base_visitor_creator.h"

std::shared_ptr<BaseVisitor> BaseVisitorCreator::getVisitor()
{
    if (!visitor)
        visitor = create();

    return visitor;
}
