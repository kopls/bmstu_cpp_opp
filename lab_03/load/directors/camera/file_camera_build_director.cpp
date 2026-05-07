#include "file_camera_build_director.h"

FileCameraBuildDirector::FileCameraBuildDirector()
    : _reader(std::make_shared<FileReader>()),
      _builder(std::make_shared<CameraBuilder>())
{
}

FileCameraBuildDirector::FileCameraBuildDirector(std::shared_ptr<BaseReader> reader,
                                                 std::shared_ptr<BaseCameraBuilder> builder)
    : _reader(reader),
      _builder(builder)
{
}

std::shared_ptr<Object> FileCameraBuildDirector::load(const std::string &fileName)
{
    _reader->open(fileName);

    auto camera = loadFromCurrentSource();

    _reader->close();

    return camera;
}

std::shared_ptr<Object> FileCameraBuildDirector::loadFromCurrentSource()
{
    _builder->build();
    _builder->buildLocation(_reader->readPoint());

    return _builder->getObject();
}
