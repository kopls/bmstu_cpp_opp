#ifndef BASE_MODEL_BUILDER_H
#define BASE_MODEL_BUILDER_H

#include <memory>

#include "base_builder.h"
#include "object.h"
#include "point.h"
#include "edge.h"

class BaseModelBuilder : public BaseBuilder
{
public:
    BaseModelBuilder() = default;
    ~BaseModelBuilder() override = default;

    virtual void buildPoint(const Point &point) = 0;
    virtual void buildEdge(const Edge &edge) = 0;

    virtual std::shared_ptr<Object> get() = 0;
};

#endif
