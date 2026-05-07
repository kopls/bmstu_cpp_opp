#include "camera_builder.h"

#include <stdexcept>

#include "camera_impl.h"

void CameraBuilder::build()
{
    _impl.reset();
}

void CameraBuilder::buildLocation(const Point &location)
{
    _impl = std::make_shared<CameraImpl>(location);
}

bool CameraBuilder::isBuild() const
{
    return _impl != nullptr;
}

std::shared_ptr<Object> CameraBuilder::getObject()
{
    return getCamera();
}

std::shared_ptr<Camera> CameraBuilder::getCamera()
{
    if (!isBuild())
        throw std::logic_error("CameraBuilder: camera is not built");

    return std::make_shared<Camera>(_impl);
}
