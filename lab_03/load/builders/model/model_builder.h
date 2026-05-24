#ifndef MODEL_BUILDER_H
#define MODEL_BUILDER_H

#include <memory>

#include "base_model_builder.h"
#include "base_model_structure.h"
#include "list_model_structure.h"
#include "matrix_model_structure.h"
#include "model_load_options.h"
#include "skeleton_model.h"

class ModelBuilder : public BaseModelBuilder
{
public:
    explicit ModelBuilder(ModelRepresentation representation = ModelRepresentation::List);
    ~ModelBuilder() override = default;

    void build() override;
    void buildPoint(const Point &point) override;
    void buildEdge(const Edge &edge) override;
    bool isBuild() const override;

    std::shared_ptr<Object> get() override;

private:
    ModelRepresentation _representation;
    std::shared_ptr<BaseModelStructure> _structure;
};

#endif
