#ifndef FILE_CAMERA_BUILD_DIRECTOR_H
#define FILE_CAMERA_BUILD_DIRECTOR_H

#include <memory>

#include "base_camera_build_director.h"
#include "base_reader.h"
#include "file_reader.h"
#include "camera_builder.h"

class FileCameraBuildDirector : public BaseCameraBuildDirector
{
public:
    FileCameraBuildDirector();
    FileCameraBuildDirector(std::shared_ptr<BaseReader> reader,
                            std::shared_ptr<BaseCameraBuilder> builder);
    ~FileCameraBuildDirector() override = default;

    std::shared_ptr<Object> load(const std::string &fileName) override;
    std::shared_ptr<Object> loadFromCurrentSource() override;

private:
    std::shared_ptr<BaseReader> _reader;
    std::shared_ptr<BaseCameraBuilder> _builder;
};

#endif
