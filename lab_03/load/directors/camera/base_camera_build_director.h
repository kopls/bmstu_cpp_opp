#ifndef BASE_CAMERA_BUILD_DIRECTOR_H
#define BASE_CAMERA_BUILD_DIRECTOR_H

#include <memory>
#include <string>

#include "base_director.h"
#include "base_camera_builder.h"
#include "object.h"

class BaseCameraBuildDirector : public BaseDirector
{
public:
    BaseCameraBuildDirector() = default;
    ~BaseCameraBuildDirector() override = default;

    virtual std::shared_ptr<Object> load(const std::string &fileName) = 0;
    virtual std::shared_ptr<Object> loadFromCurrentSource() = 0;
};

#endif
