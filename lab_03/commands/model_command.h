#ifndef COMMANDS_MODEL_COMMAND_H
#define COMMANDS_MODEL_COMMAND_H

#include <cstddef>
#include <memory>

#include "base_command.h"
#include "object.h"
#include "point.h"
#include "scene.h"
#include "transform_manager.h"

class ModelCommand : public BaseCommand
{
public:
    ~ModelCommand() override = default;
};

class MoveModel : public ModelCommand
{
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

public:
    MoveModel(std::size_t id, double dx, double dy, double dz);
    void execute() override;

private:
    Action method;
    std::size_t id;
    double dx;
    double dy;
    double dz;
};

class ScaleModel : public ModelCommand
{
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

public:
    ScaleModel(std::size_t id, double kx, double ky, double kz);
    void execute() override;

private:
    Action method;
    std::size_t id;
    double kx;
    double ky;
    double kz;
};

class RotateModel : public ModelCommand
{
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, double, double, double);

public:
    RotateModel(std::size_t id, double ox, double oy, double oz);
    void execute() override;

private:
    Action method;
    std::size_t id;
    double ox;
    double oy;
    double oz;
};

class TransformModel : public ModelCommand
{
    using Action = void (TransformManager::*)(const std::shared_ptr<Object> &, const Point &, const Point &, const Point &);

public:
    TransformModel(std::size_t id, const Point &move, const Point &scale, const Point &rotate);
    void execute() override;

private:
    Action method;
    std::size_t id;
    Point move;
    Point scale;
    Point rotate;
};

class DeleteModel : public ModelCommand
{
    using Action = void (Scene::*)(Iterator &);

public:
    explicit DeleteModel(std::size_t id);
    void execute() override;

private:
    Action method;
    std::size_t id;
};

#endif
