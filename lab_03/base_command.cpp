#icnlude "base_command.h"


void BaseCommand::setManagers(std::shared_ptr<DrawManager> drawManager, std::shared_ptr<SceneManager> sceneManager,
                              std::shared_ptr<TransformManager> transformManager, std::shared_ptr<DrawerVisitor> visitor)
{
    _drawManager = drawManager;
    _sceneManager = sceneManager;
    _transformManager = transformManager;
    _visitor = visitor;
}
