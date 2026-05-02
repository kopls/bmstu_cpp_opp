#ifndef MODEL_COMMAND_H
#define MODEL_COMMAND_H

#include <memory>
#include <cstddef>

#include "base_command.h"
#include "object.h"

class ModelCommand : public BaseCommand {};

class MoveModel : public ModelCommand
{
public:
    MoveModel(const double dx, const double dy, const double dz, const std::size_t id);
    void execute() override;

private:
    double _dx, _dy, _dz;
    std::size_t _id;
};

class ScaleModel : public ModelCommand
{
public:
    ScaleModel(const double kx, const double ky, const double kz, const std::size_t id);
    void execute() override;

private:
    double _kx, _ky, _kz;
    std::size_t _id;
};

class RotateModel : public ModelCommand
{
public:
    RotateModel(const double ox, const double oy, const double oz, const std::size_t id);
    void execute() override;

private:
    double _ox, _oy, _oz;
    std::size_t _id;
};

class TransformModel : public ModelCommand
{
public:
    TransformModel(const Point &move, const Point &scale, const Point &rotate, const std::size_t id);
    void execute() override;

private:
     Point _move, _scale, _rotate;
    std::size_t _id;
};

class DeleteModel : public ModelCommand
{
public:
    DeleteModel(const std::size_t id);
    void execute() override;

private:
    std::size_t _id;
};

#endif
