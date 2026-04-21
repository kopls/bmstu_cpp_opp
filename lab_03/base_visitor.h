#ifndef BASE_VISITOR_H
#define BASE_VISITOR_H

#include "object.h"

class BaseVisitor
{
public:
    virtual ~BaseVisitor() = 0;

    virtual void visit(Object &obj) = 0;
};

#endif
