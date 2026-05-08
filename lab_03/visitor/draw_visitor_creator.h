#ifndef DRAW_VISITOR_CREATOR_H
#define DRAW_VISITOR_CREATOR_H

#include <memory>

#include "base_visitor_creator.h"
#include "draw_visitor.h"

class DrawVisitorCreator : public BaseVisitorCreator
{
protected:
    std::shared_ptr<BaseVisitor> create() override
    {
        return std::make_shared<DrawVisitor>();
    }
};

#endif
