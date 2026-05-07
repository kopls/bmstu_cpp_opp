#include "file_scene_build_director.h"

FileSceneBuildDirector::FileSceneBuildDirector()
    : _reader(std::make_shared<FileReader>()),
      _builder(std::make_shared<SceneBuilder>())
{
    _modelDirector = std::make_shared<FileModelBuildDirector>(
        _reader,
        std::make_shared<ModelBuilder>()
    );

    _cameraDirector = std::make_shared<FileCameraBuildDirector>(
        _reader,
        std::make_shared<CameraBuilder>()
    );
}

FileSceneBuildDirector::FileSceneBuildDirector(std::shared_ptr<BaseReader> reader,
                                               std::shared_ptr<BaseSceneBuilder> builder,
                                               std::shared_ptr<BaseModelBuildDirector> modelDirector,
                                               std::shared_ptr<BaseCameraBuildDirector> cameraDirector)
    : _reader(reader),
      _builder(builder),
      _modelDirector(modelDirector),
      _cameraDirector(cameraDirector)
{
}

std::shared_ptr<Scene> FileSceneBuildDirector::load(const std::string &fileName)
{
    _reader->open(fileName);

    _builder->build();

    loadModels();
    loadCameras();

    _reader->close();

    return _builder->get();
}

void FileSceneBuildDirector::loadModels()
{
    const std::size_t count = _reader->readCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        auto model = _modelDirector->loadFromCurrentSource();
        _builder->buildObject(model);
    }
}

void FileSceneBuildDirector::loadCameras()
{
    const std::size_t count = _reader->readCount();

    for (std::size_t i = 0; i < count; ++i)
    {
        auto camera = _cameraDirector->loadFromCurrentSource();
        _builder->buildObject(camera);
    }
}
