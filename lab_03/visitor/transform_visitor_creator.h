#ifndef TRANSFORM_VISITOR_CREATOR_H
#define TRANSFORM_VISITOR_CREATOR_H

#include <memory>

#include "base_visitor_creator.h"
#include "transform_visitor.h"

class TransformVisitorCreator : public BaseVisitorCreator
{
protected:
    std::shared_ptr<BaseVisitor> create() override
    {
        return std::make_shared<TransformVisitor>();
    }
};

#endif
