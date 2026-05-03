#include "base_visitor_creator.h"

#include <memory>

BaseVisitorCreator::std::shared_ptr<BaseVisitor> getVisitor()
{
    if (!visitor)
    {
        visitor = create();
    }

    return visitor;
}
