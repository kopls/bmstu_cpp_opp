#ifndef BASE_VISITOR_CREATOR_H
#define BASE_VISITOR_CREATOR_H

#include <memory>
#include "base_visitor.h"

class BaseVisitorCreator
{
public:
    virtual ~BaseVisitorCreator() = default;

    std::shared_ptr<BaseVisitor> getVisitor();

protected:
    virtual std::shared_ptr<BaseVisitor> create() = 0;

private:
    std::shared_ptr<BaseVisitor> visitor{ nullptr };
};

#endif
