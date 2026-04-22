#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <memory>

#include "base_manager.h"
#include "base_visitor.h"
#include "scene.h"

class DrawManager : public BaseManager
{
public:
    static std::shared_ptr<DrawManager> instance(std::shared_ptr<BaseVisitor> visitor = nullptr)
    {
        class DrawManagerProxy : public DrawManager
        {
        public:
            explicit DrawManagerProxy(std::shared_ptr<BaseVisitor> visitor) : DrawManager(visitor) {} 
        };

        static auto myInstance = std::make_shared<DrawManagerProxy>(visitor);

        if (visitor && myInstance)
            myInstance->setVisitor(visitor);

        return myInstance;
    }

    ~DrawManager() = default;

    void setVisitor(std::shared_ptr<BaseVisitor> visitor);
    void drawScene(std::shared_ptr<Scene> scene);

private:
    explicit DrawManager(std::shared_ptr<BaseVisitor> visitor) : _visitor(visitor) {} 

    std::shared_ptr<BaseVisitor> _visitor;
};

#endif
