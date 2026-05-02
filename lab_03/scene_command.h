#ifndef SCENE_COMMAND_H
#define SCENE_COMMAND_H

#include <memory>

#include "base_command.h"

class SceneCommand : public BaseCommand { };

class DrawScene : public SceneCommand
{
public:
    DrawScene(std::shared_ptr<BaseDrawer> drawer);

    void execute() override;

private:
    std::shared_ptr<BaseDrawer> _drawer;
};


class LoadScene : public SceneCommand
{
public:
    LoadScene(std::string fileName);

    void execute() override;

private:
    std::string _fileName;
};

#endif //SCENECOMMAND_H
