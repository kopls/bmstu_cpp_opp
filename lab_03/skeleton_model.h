#ifndef SKELETON_MODEL_H
#define SKELETON_MODEL_H

#include "base_model.h"
#include "base_model_structure.h"

class Visitor;

class SkeletonModel : public BaseModel
{
public:
    explicit SkeletonModel(const std::shared_ptr<BaseModelStructure> &modelStructure) : _modelStructure(modelStructure) {}
    // SkeletonModel(const SkeletonModel &model);

    ~SkeletonModel() override = default;

    void accept(Visitor &visitor) override;

    //std::shared_ptr<BaseModelStructure> getStructure() const { return _modelStructure; } либо гетер, либо общий доступ, без дружбы никак

//protected:
    std::shared_ptr<BaseModelStructure> _modelStructure;
};

#endif
