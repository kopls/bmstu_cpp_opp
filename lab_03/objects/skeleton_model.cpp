#include "skeleton_model.h"
#include "base_visitor.h"

void SkeletonModel::accept(BaseVisitor &visitor)
{
    visitor.visit(*this);
}

std::shared_ptr<Object> SkeletonModel::clone() const
{
    auto structure = _modelStructure ? _modelStructure->clone() : nullptr;
    auto model = std::make_shared<SkeletonModel>(structure);
    model->_id = _id;
    return model;
}
