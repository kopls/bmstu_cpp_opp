#ifndef CAMERA_COMMAND_H
#define CAMERA_COMMAND_H

#include <memory>
#include <cstddef>

#include "base_command.h"
#include "camera.h"

using ID = std::shared_ptr<std::size_t>;

class CameraCommand : public BaseCommand {};

class AddCamera: public CameraCommand
{
public:
    AddCamera(const ID &id, const double x, const double y, const double z);

    void execute() override;

private:
    double _x, _y, _z;
    ID _id;
};


class DeleteCamera: public CameraCommand
{
public:
    DeleteCamera(const std::size_t id);

    void execute() override;

private:
    std::size_t _id;
};


class MoveCamera: public CameraCommand
{
public:
    MoveCamera(const double dx, const double dy, const double dz, const std::size_t id);

    void execute() override;

private:
    double _dx, _dy, _dz;
    std::size_t _id;
};


class SetCamera: public CameraCommand
{
public:
    explicit SetCamera(const std::size_t id);

    void execute() override;

private:
    std::size_t _id;
};

#endif 
