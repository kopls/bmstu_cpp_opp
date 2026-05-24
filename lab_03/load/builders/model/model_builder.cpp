#include "model_builder.h"

#include <stdexcept>

ModelBuilder::ModelBuilder(ModelRepresentation representation)
    : _representation(representation)
{
}

void ModelBuilder::build()
{
    if (_representation == ModelRepresentation::Matrix)
        _structure = std::make_shared<MatrixModelStructure>();
    else
        _structure = std::make_shared<ListModelStructure>();
}

void ModelBuilder::buildPoint(const Point &point)
{
    if (!isBuild())
        throw std::logic_error("ModelBuilder: structure is not built");

    _structure->addPoint(point);
}

void ModelBuilder::buildEdge(const Edge &edge)
{
    if (!isBuild())
        throw std::logic_error("ModelBuilder: structure is not built");

    _structure->addEdge(edge);
}

bool ModelBuilder::isBuild() const
{
    return _structure != nullptr;
}

std::shared_ptr<Object> ModelBuilder::get()
{
    if (!isBuild())
        throw std::logic_error("ModelBuilder: model is not built");

    return std::make_shared<SkeletonModel>(_structure);
}
