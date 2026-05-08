#ifndef SKELETON_MODEL_H
#define SKELETON_MODEL_H

#include <memory>

#include "base_model.h"
#include "base_model_structure.h"

class BaseVisitor;

class SkeletonModel : public BaseModel
{
public:
    explicit SkeletonModel(const std::shared_ptr<BaseModelStructure> &modelStructure) : _modelStructure(modelStructure) {}

    ~SkeletonModel() override = default;

    void accept(BaseVisitor &visitor) override;

    //std::shared_ptr<BaseModelStructure> getStructure() const { return _modelStructure; } либо гетер, либо общий доступ, без дружбы никак

//protected:
    std::shared_ptr<BaseModelStructure> _modelStructure;
};

#endif
