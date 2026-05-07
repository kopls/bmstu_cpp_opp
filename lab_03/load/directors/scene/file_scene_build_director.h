#ifndef FILE_SCENE_BUILD_DIRECTOR_H
#define FILE_SCENE_BUILD_DIRECTOR_H

#include <memory>

#include "base_scene_build_director.h"
#include "base_reader.h"
#include "file_reader.h"
#include "scene_builder.h"
#include "base_model_build_director.h"
#include "file_model_build_director.h"
#include "base_camera_build_director.h"
#include "file_camera_build_director.h"

class FileSceneBuildDirector : public BaseSceneBuildDirector
{
public:
    FileSceneBuildDirector();
    FileSceneBuildDirector(std::shared_ptr<BaseReader> reader,
                           std::shared_ptr<BaseSceneBuilder> builder,
                           std::shared_ptr<BaseModelBuildDirector> modelDirector,
                           std::shared_ptr<BaseCameraBuildDirector> cameraDirector);
    ~FileSceneBuildDirector() override = default;

    std::shared_ptr<Scene> load(const std::string &fileName) override;

private:
    void loadModels();
    void loadCameras();

    std::shared_ptr<BaseReader> _reader;
    std::shared_ptr<BaseSceneBuilder> _builder;
    std::shared_ptr<BaseModelBuildDirector> _modelDirector;
    std::shared_ptr<BaseCameraBuildDirector> _cameraDirector;
};

#endif
