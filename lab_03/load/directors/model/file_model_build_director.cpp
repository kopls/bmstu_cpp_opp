#include "file_model_build_director.h"

FileModelBuildDirector::FileModelBuildDirector()
    : _reader(std::make_shared<FileReader>()),
      _builder(std::make_shared<ModelBuilder>())
{
}

FileModelBuildDirector::FileModelBuildDirector(std::shared_ptr<BaseReader> reader,
                                               std::shared_ptr<BaseModelBuilder> builder)
    : _reader(reader),
      _builder(builder)
{
}

std::shared_ptr<Object> FileModelBuildDirector::load(const std::string &fileName)
{
    _reader->open(fileName);

    auto model = loadFromCurrentSource();

    _reader->close();

    return model;
}

std::shared_ptr<Object> FileModelBuildDirector::loadFromCurrentSource()
{
    _builder->build();

    const auto points = _reader->readPoints();
    const auto edges = _reader->readEdges(points.size());

    for (const auto &point : points)
        _builder->buildPoint(point);

    for (const auto &edge : edges)
        _builder->buildEdge(edge);

    return _builder->get();
}
